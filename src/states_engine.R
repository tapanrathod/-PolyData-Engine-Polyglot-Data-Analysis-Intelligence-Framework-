args <- commandArgs(trailingOnly = TRUE)

if (length(args) == 0) {
  stop("Usage: Rscript stats_engine.R <csv_path>", call. = FALSE)
}

csv_path <- args[1]
cat("\n📊 [R Engine] Running Statistical Profiling...\n")

data <- read.csv(csv_path)
numeric_data <- data[sapply(data, is.numeric)]

if (ncol(numeric_data) > 0) {
  cat("\n--- Normality Test (Shapiro-Wilk) ---\n")
  for (col in colnames(numeric_data)) {
    vals <- na.omit(numeric_data[[col]])
    if (length(vals) >= 3 && length(vals) <= 5000) {
      test <- shapiro.test(vals)
      cat(sprintf("Column: %-15s | p-value: %.5f\n", col, test$p.value))
    }
  }
} else {
  cat("No numeric columns available for statistical testing.\n")
}
