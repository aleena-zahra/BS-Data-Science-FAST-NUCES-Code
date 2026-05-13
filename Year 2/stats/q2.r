# (Install packages if needed)
# install.packages("ggplot2")
# install.packages("GGally")
# install.packages("car")

library(ggplot2)
library(GGally)
library(car)

# (Data)
Y <- c(2.1, 2.5, 3.0, 3.3, 3.5)
X1 <- c(2, 3, 4, 5, 6)
X2 <- c(10, 8, 5, 3, 2)
data <- data.frame(Y, X1, X2)

# (a) Scatter Plot Matrix
ggpairs(data)

# (b) Correlation Matrix
cor(data)

# (c) Regression
model <- lm(Y ~ X1 + X2, data=data)
summary(model)

# (d) Variance-Covariance Matrix
vcov(model)

# (e) Hypothesis Testing is in summary(model) (t-statistics and p-values)

# (f) Confidence Intervals
confint(model)

# (g) Predict CGPA for X1=1, X2=4
predict(model, data.frame(X1=1, X2=4))

# (h) SSR, SSE, SST
y_hat <- predict(model)
SSR <- sum((y_hat - mean(Y))^2)
SSE <- sum((Y - y_hat)^2)
SST <- sum((Y - mean(Y))^2)
cat("SSR:", SSR, "SSE:", SSE, "SST:", SST, "\n")

# (i) R-squared
summary(model)$r.squared

# (j) ANOVA
anova(model)
