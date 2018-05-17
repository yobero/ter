g = read.table("result")
jpeg("plot.jpg")
plot(g$V1, g$V2, type = "n", ylim = range(c(g$V2, g$V3)), xlab = "", ylab = "")
lines(g$V1, g$V2, col = "blue")
lines(g$V1, g$V3, col = "red")
dev.off()