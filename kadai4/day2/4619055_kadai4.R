#4619055 辰川力駆

#手順4
(Y <- matrix(c(10,20,20,40,40,5),nrow=6,ncol=1))

(X <- matrix(c(rep(1,6),1,2,3,3,5,1),nrow=6,ncol=2))

#手順5
#(a)
xbar <- mean(X[,2])
#(b)
ybar <- mean(Y)
##結果表示
data.frame(x.mean = xbar, y.mean = ybar)

#(c)
xSSD <- sum((X[,2]-xbar)^2)
#(d)
ySSD <- sum((Y-ybar)^2)
##結果表示
data.frame(x.SSD = xSSD, y.SSD = ySSD)

#手順6
#(a)
(beta <- solve(t(X) %*% X) %*% t(X) %*% Y)
#(b)
yhat <- X %*% beta 
#(c)
e <- Y - yhat
##結果表示
data.frame(y=Y,yhat=yhat,e=e)

##実験手順7
##射影行列の定義
(H <- X %*% solve(t(X) %*% X) %*% t(X))

#(a)
t(H)
##対称性が成立しているか確認
sum((t(H)-H)^2)

#(b)
H %*% H
##べき等性が成立しているか確認
sum((H %*% H-H)^2)
#(c)
sum(diag(H))


##実験手順8
##モデル平方和
MSS <- sum((yhat - mean(yhat))^2)
##残差平方和
RSS <- sum(e^2)
##総平方和
TSS <- MSS + RSS
##結果表示
data.frame(ySSD = ySSD, TSS = TSS)

##実験手順9
##寄与率
MSS/TSS
R2 <- MSS/TSS
##相関係数の絶対値
sqrt(MSS/TSS)