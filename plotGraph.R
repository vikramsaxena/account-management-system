# Read data from portfolio_history.txt with specific column widths
data <- read.fwf("portfolio_history.txt", widths=c(20, 20, 24), col.names=c("portfolioValue", "balance", "time"))

# Check if the data was read successfully
if (nrow(data) > 0) {
  # Convert the time column to POSIXct
  data$time <- strptime(data$time, format="%a_%b_%d_%H:%M:%S_%Y")
  
  # Calculate change in portfolio value
  data$portfolioChange <- c(NA, diff(data$portfolioValue))
  
  # Plotting Change in Portfolio Value vs Time
  plot(data$time, data$portfolioChange, type='b', col='blue', xlab='Time', ylab='Change in Portfolio Value', main='Change in Portfolio Value over Time')

  # Plotting Actual Portfolio Value vs Time
  plot(data$time, data$portfolioValue, type='b', col='red', xlab='Time', ylab='Portfolio Value', main='Actual Portfolio Value over Time')
} else {
  cat("Error: Unable to read data from", file_path, "\n")
}