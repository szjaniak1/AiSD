import numpy
import matplotlib.pyplot as plt
import seaborn as sns
import pandas as pd

df = pd.read_csv("./data/sortingAlgResults.csv", header=0, delimiter=";")
df["c/n"] = df["comp"]/df["n"]
df["s/n"] = df["shifts"]/df["n"]
sns.set_style("darkgrid")

plt.title("shift")
sns.lineplot(data=df, x='n', y ='shifts', hue="type")
plt.savefig('plots/shift.png')
plt.clf()

plt.title("comparisons")
sns.lineplot(data=df, x='n', y='comp', hue="type")
plt.savefig('plots/cmps.png')
plt.clf()

plt.title("c/n")
sns.lineplot(data=df, x='n', y='c/n', hue="type")
plt.savefig('plots/cn.png')
plt.clf()

plt.title("s/n")
sns.lineplot(data=df, x='n', y='s/n', hue="type")
plt.savefig('plots/sn.png')
plt.clf()
