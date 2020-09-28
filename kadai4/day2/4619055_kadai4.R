#4619055 辰川力駆
(Y <- matrix(c(10,20,20,40,40,5),nrow=6,ncol=1))

(X <- matrix(c(rep(1,6),1,2,3,3,5,1),nrow=6,ncol=2))

xbar <- mean(X[,2])
ybar <- mean(Y)

data.frame(x.mean = xbar, y.mean = ybar)


xssd <- sum((X[,2]-xbar)^2)
yssd <- sum((Y-ybar)^2)

data.frame(x.ssd = xssd, y.ssd = yssd)


(beta <- solve(t(X) %*% X) %*% t(X) %*% Y)

yhat <- X %*% beta 

e <- Y - yhat

data.frame(y=Y,yhat=yhat,e=e)

#実験手順7
(H <- X %*% solve(t(X) %*% X) %*% t(X))

t(H)
sum((t(H)-H)^2)

H %*% H

sum(diag(H))

#実験手順8
MSS <- sum((yhat - mean(yhat))^2)
RSS <- sum(e^2)
TSS <- MSS + RSS
data.frame(ySSD = yssd, TSS = TSS)

#実験手順9
MSS/TSS
R2 <- MSS/TSS
sqrt(MSS/TSS)


