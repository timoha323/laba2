import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('performance_results.csv')

generators = data['Data Generator'].unique()
sorters = data['Sorter'].unique()

for generator in generators:
    plt.figure(figsize=(10, 6))
    for sorter in sorters:
        subset = data[(data['Data Generator'] == generator) & (data['Sorter'] == sorter)]
        plt.plot(subset['Data Size'], subset['Average Time (seconds)'], label=sorter, marker='o')

    plt.title(f"Sorting Performance for {generator}")
    plt.xlabel("Data Size")
    plt.ylabel("Average Time (seconds)")
    plt.legend(title="Sorter")
    plt.grid(True)
    plt.savefig(f"plot_{generator.replace(' ', '_').replace('(', '').replace(')', '')}.png")
    plt.close()
