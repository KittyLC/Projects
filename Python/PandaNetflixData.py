from matplotlib import pyplot as plt
import pandas as pd
import seaborn as sns

netflix_stocks = pd.read_csv("NFLX.csv")
print(netflix_stocks.head())
dowjones_stocks = pd.read_csv("DJI.csv")
print(dowjones_stocks.head())
netflix_stocks_quarterly = pd.read_csv("NFLX_daily_by_quarter.csv")
print(netflix_stocks_quarterly.head())

print("Netflix Stocks: {}".format(netflix_stocks.columns.values.tolist()))
print("Earliest Date {}\nLatest Date: {}".format(netflix_stocks["Date"].min(), netflix_stocks["Date"].max()))

print("Dow Jones Industrial Average: {}".format(dowjones_stocks.columns.values.tolist()))
print("Earliest Date {}\nLatest Date: {}".format(dowjones_stocks["Date"].min(), dowjones_stocks["Date"].max()))

print("Netflix Stocks Daily: {}".format(netflix_stocks_quarterly.columns.values.tolist()))
print("Earliest Date {}\nLatest Date: {}".format(netflix_stocks_quarterly["Date"].min(), netflix_stocks_quarterly["Date"].max()))

print(netflix_stocks.head())

netflix_stocks.rename(columns={"Adj Close": "Price"}, inplace=True)
dowjones_stocks.rename(columns={"Adj Close": "Price"}, inplace=True)
netflix_stocks_quarterly.rename(columns={"Adj Close": "Price"}, inplace=True)

print(netflix_stocks.head())
print(dowjones_stocks.head())
print(netflix_stocks_quarterly.head())

plt.figure(figsize=(10, 10))
sns.set(style="whitegrid")
ax = sns.violinplot(x=netflix_stocks_quarterly["Quarter"], y=netflix_stocks_quarterly["Price"], data=netflix_stocks_quarterly)
ax.set_title("Distribution of 2017 Netflix Stock Prices by Quarter", fontsize=14)
ax.set_xlabel("Business Quarters in 2017")
ax.set_ylabel("Closing Stock Price")
ax.set_yticks(list(range(120, 220, 10)))
plt.savefig('Distribution of Netflix Stock Prices by Quarter.png')
plt.show()

plt.close()
plt.figure(figsize=(10,10))
x_positions = [1, 2, 3, 4]
chart_labels = ["1Q2017","2Q2017","3Q2017","4Q2017"]
earnings_actual =[.4, .15,.29,.41]
earnings_estimate = [.37,.15,.32,.41 ]

ax = plt.subplot()
plt.scatter(x_positions, earnings_actual, c='red', alpha=0.5, linewidths=3)
plt.scatter(x_positions, earnings_estimate, c='blue', alpha=0.5, linewidths=3)
plt.grid(b=True)
plt.xticks(x_positions, chart_labels)
ax.set_title("Earnings Per Share in Cents", fontsize=14)
ax.set_xlabel("Quarters")
ax.set_ylabel("Earnings in Cents")
box = ax.get_position()
ax.set_position([box.x0, box.y0, box.width * 0.8, box.height]) 
ax.legend(["Actual", "Estimate"], shadow=True, fancybox=True, bbox_to_anchor=(1.2, 1))
plt.savefig('Earnings Per Share in Cents.png')
plt.show()

plt.close()

revenue_by_quarter = [2.79, 2.98,3.29,3.7]
earnings_by_quarter = [.0656,.12959,.18552,.29012]
quarter_labels = ["2Q2017","3Q2017","4Q2017", "1Q2018"]


n = 1  
t = 2 
d = len(quarter_labels) 
w = 0.8 
bars1_x = [t*element + w*n for element
             in range(d)]

n = 2 
t = 2
d = len(quarter_labels) 
w = 0.8 
bars2_x = [t*element + w*n for element
             in range(d)]

middle_x = [ (a + b) / 2.0 for a, b in zip(bars1_x, bars2_x)]
labels = ["Revenue", "Earnings"]

plt.figure(figsize=(10,10))
ax = plt.subplot()
plt.bar(bars1_x, revenue_by_quarter, color='b')
plt.bar(bars2_x, earnings_by_quarter, color='g')
ax.set_title("Revenue vs. Earnings Quarterly", fontsize=14)
ax.set_xlabel("Quarters")
ax.set_ylabel("Billions of Dollars")
plt.xticks(middle_x, quarter_labels)
plt.legend(labels)
plt.savefig('Revenue vs Earnings Quarterly.png')
plt.show()

plt.close()
ratios = []
for i in range(len(revenue_by_quarter)):
    ratios.append(earnings_by_quarter[i] / revenue_by_quarter[i] * 100)
print(ratios)
print("{:.2f}%".format(sum(ratios) / len(ratios)))

compfig = plt.figure(figsize=(16,10))
month_names = ['Jan', 'Feb', 'Mar', 'Apr', 'May', 'June', 'July', 'Aug', 'Sept', 'Oct', 'Nov', 'Dec']
compfig.suptitle("How did Netflix do relative to the Dow Jones Index?", fontsize=16)

ax1 = plt.subplot(1, 2, 1)
plt.plot(netflix_stocks["Date"], netflix_stocks["Price"], 'o', netflix_stocks["Date"], netflix_stocks["Price"], '-')
ax1.set_title("Netflix", fontsize=14)
ax1.set_xlabel("Date")
ax1.set_ylabel("Stock Price")
ax1.set_xticklabels(month_names)

ax2 = plt.subplot(1, 2, 2)
plt.plot(dowjones_stocks["Date"], dowjones_stocks["Price"], 'o', dowjones_stocks["Date"], dowjones_stocks["Price"], '-')
ax2.set_title("Dow Jones", fontsize=14)
ax2.set_xlabel("Date")
ax2.set_ylabel("Stock Price")
ax2.set_xticklabels(month_names)

plt.subplots_adjust(wspace=0.5)
plt.savefig('Netflix and Dow Jones Stocks 2017.png')
plt.show()

plt.close()
print("Checking how the stocks of netflix and the dow jones index compare")
print("Jan 2017\nNetflix: {:.2f} vs. Dow Jones: {:.2f}".format(netflix_stocks[netflix_stocks["Date"] == '2017-01-01']["Price"][0], dowjones_stocks[dowjones_stocks["Date"] == '2017-01-01']["Price"][0]))
print("Ratio of {:.4f}".format(netflix_stocks[netflix_stocks["Date"] == '2017-01-01']["Price"][0] / dowjones_stocks[dowjones_stocks["Date"] == '2017-01-01']["Price"][0]))


