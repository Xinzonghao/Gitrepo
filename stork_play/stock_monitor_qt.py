import sys
import yfinance as yf
import matplotlib.pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar

from PyQt5.QtWidgets import (
    QApplication, QWidget, QLabel, QLineEdit, QPushButton,
    QVBoxLayout, QHBoxLayout, QMessageBox, QScrollArea, QFrame, QComboBox,
)
from PyQt5.QtGui import QFont
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QSizePolicy
from PyQt5.QtGui import QMovie
import mplfinance as mpf
import pandas as pd
import socket
from forex_python.converter import CurrencyRates
import requests
import datetime


# Index ticker mapping
INDEX_TICKERS = {
    "NASDAQ": "^IXIC",
    "Nikkei 225": "^N225",
    "CSI 300": "000300.SS",
    "S&P 500": "^GSPC",
    "Dow Jones": "^DJI",
}


class IndexTrendPlot(QWidget):
    def __init__(self, index_name, ticker, period='1d', interval='5m'):
        super().__init__()
        self.index_name = index_name
        self.ticker = ticker
        self.period = period
        self.interval = interval
        self.setFixedHeight(200)  # 🧱 lock plot height
        self.setSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        self.init_ui()

    def init_ui(self):
        layout = QVBoxLayout()
        self.figure, self.ax = plt.subplots(facecolor="black")
        self.canvas = FigureCanvas(self.figure)
        layout.addWidget(QLabel(f"<b style='color:white'>{self.index_name}</b>"))
        layout.addWidget(self.canvas)
        # self.toolbar = NavigationToolbar(self.canvas, self)

        # # Add both toolbar and canvas to layout
        # layout.addWidget(self.toolbar)
        # layout.addWidget(self.canvas)
        self.setLayout(layout)
        self.plot_trend()

    def plot_trend(self):
        self.ax.clear()
        try:
            data = yf.Ticker(self.ticker).history(period=self.period, interval=self.interval)
            self.ax.set_facecolor("black")
            self.ax.spines['top'].set_visible(False)
            self.ax.spines['right'].set_visible(False)
            self.ax.spines['bottom'].set_color("gray")
            self.ax.spines['left'].set_color("gray")
            self.ax.tick_params(colors='white')
            self.ax.yaxis.label.set_color('white')
            self.ax.xaxis.label.set_color('white')
            self.ax.title.set_color('white')

            if data.empty:
                self.ax.text(0.5, 0.5, "No data", ha='center', va='center', color='white')
            else:
                self.ax.plot(data.index, data['Close'], label="Price", color="#00FFAA")
                # self.ax.set_title(f"{self.index_name}", fontsize=10)
                # self.ax.set_xlabel("Time", fontsize=8)
                # Moving Averages
                if len(data) >= 20:
                    data['MA20'] = data['Close'].rolling(window=20).mean()
                    self.ax.plot(data.index, data['MA20'], label="MA20", color="#FFAA00", linestyle='--')
                if len(data) >= 50:
                    data['MA50'] = data['Close'].rolling(window=50).mean()
                    self.ax.plot(data.index, data['MA50'], label="MA50", color="#AA00FF", linestyle=':')
                self.ax.set_ylabel("Price", fontsize=8)
                self.ax.grid(True, color='gray', linestyle='--', linewidth=0.5)
                self.ax.tick_params(axis='x', labelrotation=45, labelsize=6)
                self.ax.legend(fontsize=7)
                
                self.figure.tight_layout()
        except Exception as e:
            self.ax.text(0.5, 0.5, f"Error: {e}", ha='center', va='center', color='red')

        self.canvas.draw()
    
    # def plot_trend(self):
    #     self.ax.clear()
    #     try:
    #         data = yf.Ticker(self.ticker).history(period=self.period, interval=self.interval)
    #         self.ax.set_facecolor("black")

    #         if data.empty:
    #             self.ax.text(0.5, 0.5, "No data", ha='center', va='center', color='white')
    #         else:
    #             # Prepare data for candlestick plotting
    #             df = data[['Open', 'High', 'Low', 'Close']].copy()
    #             df.index.name = 'Date'

    #             # Clear previous axes (mplfinance reuses figure but makes its own Axes)
    #             self.figure.clf()
    #             ax = self.figure.add_subplot(111)

    #             mpf.plot(
    #                 df,
    #                 type='candle',
    #                 ax=ax,
    #                 style=mpf.make_mpf_style(base_mpf_style='nightclouds', facecolor='black'),
    #                 datetime_format='%m-%d %H:%M' if self.period == "1d" else '%Y-%m-%d',
    #                 xrotation=15,
    #                 show_nontrading=False
    #             )

    #     except Exception as e:
    #         self.ax.text(0.5, 0.5, str(e), color="red", ha="center")

    #     self.canvas.draw()

    def update_period(self, period, interval):
        self.period = period
        self.interval = interval
        self.plot_trend()


class StockMonitor(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("📈 Stock Monitor Dashboard")
        self.setGeometry(100, 100, 1200, 700)
        self.setStyleSheet("background-color: #1c1c1c; color: white;")
        self.init_ui()

    def init_ui(self):
        main_layout = QHBoxLayout()
        self.setLayout(main_layout)

        # ── Left Panel ─────────────────────────────
        left_panel = QVBoxLayout()

        title = QLabel("💹 Stock Monitor")
        title.setFont(QFont("Arial", 16))
        title.setStyleSheet("color: #00FFAA;")
        left_panel.addWidget(title)

        left_panel.addWidget(QLabel("Enter Stock Symbol:"))
        self.input = QLineEdit()
        self.input.setPlaceholderText("e.g. AAPL, TSLA, 7203.T")
        self.input.setStyleSheet("background-color: #333; color: white;")
        left_panel.addWidget(self.input)

        self.price_label = QLabel("")
        self.price_label.setStyleSheet("font-size: 14px;")
        left_panel.addWidget(self.price_label)

        self.button = QPushButton("Get Current Price")
        self.button.clicked.connect(self.get_price)
        self.button.setStyleSheet("background-color: #00FFAA;")
        left_panel.addWidget(self.button)

        self.trend_button = QPushButton("Show Price Trend")
        self.trend_button.clicked.connect(self.show_trend)
        self.trend_button.setStyleSheet("background-color: #00BFFF;")
        left_panel.addWidget(self.trend_button)

        left_panel.addStretch()
        main_layout.addLayout(left_panel, 1)

        # select period
        self.plot_widgets = []

        button_layout = QHBoxLayout()
        left_panel.addWidget(QLabel("Select Trend Period:"))

        # for button
        for label, period, interval in [
            ("1D", "1d", "5m"),
            ("1W", "7d", "30m"),
            ("1M", "1mo", "1d"),
            ("1Y", "1y", "1d"),
        ]:
            btn = QPushButton(label)
            btn.clicked.connect(lambda checked, p=period, i=interval: self.update_all_plots(p, i))
            button_layout.addWidget(btn)

        left_panel.addLayout(button_layout)

        # ── Right Panel: Scrollable Trend Area ─────
        scroll_area = QScrollArea()
        scroll_area.setStyleSheet("background-color: #121212;")
        frame = QFrame()
        index_layout = QVBoxLayout()
        frame.setLayout(index_layout)

        for name, ticker in INDEX_TICKERS.items():
            plot_widget = IndexTrendPlot(name, ticker)
            index_layout.addWidget(plot_widget)
            self.plot_widgets.append(plot_widget)

        scroll_area.setWidget(frame)
        scroll_area.setWidgetResizable(True)
        main_layout.addWidget(scroll_area, 2)

        # ── Exchange Rates ────────────────────────
        rate_box_layout = QVBoxLayout()
        rate_box_layout.setAlignment(Qt.AlignCenter)  # ⬅️ Center vertically and horizontally

        self.jpy_cny_label = QLabel()
        self.cny_usd_label = QLabel()
        self.jpy_cny_label.setStyleSheet("color: white;")
        self.cny_usd_label.setStyleSheet("color: white;")
        self.jpy_cny_label.setAlignment(Qt.AlignCenter)
        self.cny_usd_label.setAlignment(Qt.AlignCenter)

        font = QFont("Arial", 16, QFont.Bold)
        self.jpy_cny_label.setFont(font)
        self.cny_usd_label.setFont(font)
        
        rate_box_layout.addWidget(self.jpy_cny_label)
        rate_box_layout.addWidget(self.cny_usd_label)
        rate_box_widget = QWidget()
        rate_box_widget.setLayout(rate_box_layout)  
        
        left_panel.addWidget(rate_box_widget)
        left_panel.addStretch()

        self.update_exchange_rates()

    def get_price(self):
        ticker = self.input.text().upper()
        if not ticker:
            QMessageBox.warning(self, "Input Error", "Please enter a stock symbol.")
            return
        try:
            stock = yf.Ticker(ticker)
            price = stock.info["currentPrice"]
            self.price_label.setText(f"{ticker} Price: ${price:.2f}")
        except Exception as e:
            if isinstance(e, (socket.gaierror, ConnectionError, TimeoutError)):
                QMessageBox.critical(self, "Network Error", "Failed to fetch price: Please check your internet connection.")
            else:
                QMessageBox.critical(self, "Error", f"Failed to fetch price: {e}")

    def show_trend(self):
        ticker = self.input.text().upper()
        if not ticker:
            QMessageBox.warning(self, "Input Error", "Please enter a stock symbol.")
            return
        try:
            data = yf.Ticker(ticker).history(period="1d", interval="5m")
            if data.empty:
                QMessageBox.warning(self, "No Data", "No historical data found.")
                return
            plt.style.use("dark_background")
            plt.figure(figsize=(8, 4))
            plt.plot(data.index, data["Close"], label="Close Price", color="#00FFAA")
            plt.title(f"{ticker} Price Trend - 1 Day")
            plt.xlabel("Time")
            plt.ylabel("Price ($)")
            plt.grid(True, linestyle='--', linewidth=0.5, color='gray')
            plt.xticks(rotation=45)
            plt.tight_layout()
            plt.show()
        except Exception as e:
            if isinstance(e, (socket.gaierror, ConnectionError, TimeoutError)):
                QMessageBox.critical(self, "Network Error", "Failed to fetch price: Please check your internet connection.")
            else:
                QMessageBox.critical(self, "Error", f"Failed to fetch price: {e}")
        
    def update_all_plots(self, period, interval):
        for plot_widget in self.plot_widgets:
            plot_widget.update_period(period, interval)

    def get_yesterday_rate(self, base, target, amount=1):
        try:
            yesterday = (datetime.datetime.now() - datetime.timedelta(days=3)).strftime("%Y-%m-%d")
            res = requests.get(
                f"https://api.frankfurter.app/{yesterday}",
                params={"from": base, "to": target, "amount": amount}
            )
            return res.json()["rates"][target]
        except Exception as e:
            print(f"Error fetching yesterday's rate: {e}")
            return None

    def update_exchange_rates(self):
        amount_jpy = 10000
        try:
            yesterday_jpy_cny = self.get_yesterday_rate("JPY", "CNY", amount=amount_jpy)
            yesterday_cny_usd = self.get_yesterday_rate("USD", "CNY", amount=1)
            # Get JPY to CNY rate from frankfurter
            resp1 = requests.get("https://api.frankfurter.app/latest?amount=10000&from=JPY&to=CNY")
            jpy_cny = resp1.json()['rates']['CNY']

            # Get CNY to USD
            resp2 = requests.get("https://api.frankfurter.app/latest?amount=1&from=USD&to=CNY")
            cny_usd = resp2.json()['rates']['CNY']

            # display the rates
            if jpy_cny is not None and yesterday_jpy_cny is not None:
                symbol = "▲" if jpy_cny > yesterday_jpy_cny else "▼" if jpy_cny < yesterday_jpy_cny else ""
                color = "red" if jpy_cny > yesterday_jpy_cny else "green" if jpy_cny < yesterday_jpy_cny else "white"
                self.jpy_cny_label.setText(
                    f'<span style="font-size:18pt; color:{color};">'
                    f'{symbol} ¥{amount_jpy} JPY = {jpy_cny:.2f} ¥CNY</span>'
                )
            
            if cny_usd is not None and yesterday_cny_usd is not None:
                symbol = "▲" if cny_usd > yesterday_cny_usd else "▼" if cny_usd < yesterday_cny_usd else ""
                color = "red" if cny_usd > yesterday_cny_usd else "green" if cny_usd < yesterday_cny_usd else "white"
                self.cny_usd_label.setText(
                    f'<span style="font-size:18pt; color:{color};">'
                    f'{symbol} $1 USD = {cny_usd:.2f} ¥CNY</span>'
                )
            else:
                self.jpy_cny_label.setText("Rate not available")
                self.cny_usd_label.setText("Rate not available")


        except Exception as e:
            self.jpy_cny_label.setText(f"Rate error: {e}")
            self.cny_usd_label.setText(f"Rate error: {e}")


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = StockMonitor()
    window.show()
    sys.exit(app.exec_())
