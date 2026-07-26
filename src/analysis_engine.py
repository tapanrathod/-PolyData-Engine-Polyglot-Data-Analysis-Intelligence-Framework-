import sys
import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

def run_python_analysis(csv_path):
    print("\n🐍 [Python Engine] Loading and Processing Dataset...")
    df = pd.read_csv(csv_path)

    # 1. Automatic Data Cleaning
    initial_shape = df.shape
    df.drop_duplicates(inplace=True)
    
    # Fill numeric missing values with median
    numeric_cols = df.select_dtypes(include=[np.number]).columns
    for col in numeric_cols:
        df[col].fillna(df[col].median(), inplace=True)

    print(f"Dataset Shape: {initial_shape} -> Cleaned Shape: {df.shape}")

    # 2. Summary Table Generation
    os.makedirs("output", exist_ok=True)
    summary = df.describe().T
    summary.to_csv("output/summary_statistics.csv")
    print("✓ Saved summary statistics to output/summary_statistics.csv")

    # 3. Automated Heatmap Plotting
    if len(numeric_cols) > 1:
        plt.figure(figsize=(10, 6))
        sns.heatmap(df[numeric_cols].corr(), annot=True, cmap="viridis", fmt=".2f")
        plt.title("Automated Correlation Matrix")
        plt.tight_layout()
        plt.savefig("output/correlation_matrix.png")
        plt.close()
        print("✓ Generated output/correlation_matrix.png")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python analysis_engine.py <csv_path>")
        sys.exit(1)
    run_python_analysis(sys.argv[1])
