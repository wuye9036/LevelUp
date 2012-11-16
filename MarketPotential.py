import arcgisscripting, sys, os

if __name__ == "__main__":
	#初始化GP
	gp = arcgisscripting.create()
	gp.overwriteoutput = 1
	
	#获取参数
	marketsFeatCls = sys.argv[1]
	marketsFeatClsOIDFieldName = gp.Describe(marketsFeatCls).OIDFieldName
	
	#读取数据
	marketsDict = {}
	marketsIncoming = {}
	marketsIter = gp.SearchCursor( marketsFeatCls )
	market = marketsIter.next()
	while market:
		#读取点坐标
		marketCentroid = market.shape.TrueCentroid
		marketId = market.GetValue(marketsFeatClsOIDFieldName)
		marketPosition = ( float(marketCentroid.split(' ')[0]),  float(marketCentroid.split(' ')[1]) )
		marketsDict[marketId] = marketPosition
		
		marketsIncoming[marketId] = market.GetValue("TOTALINCOM")
		market = marketsIter.next()
	del market
	del marketsIter
	
	#计算
	marketPotentialDict = {}
	for srcMarketId in marketsDict.keys():
		srcPoint = marketsDict[srcMarketId]
		srcPotential = 0.0
		
		for destMarketId in marketsDict.keys():
			if srcMarketId == destMarketId:	
				continue
			destPoint = marketsDict[destMarketId]
			distSqr = (srcPoint[0] - destPoint[0]) ** 2 + (srcPoint[1] - destPoint[1]) ** 2
			dist = distSqr ** 0.5
			srcPotential  += marketsIncoming[destMarketId] / dist
	
		marketPotentialDict[srcMarketId] = srcPotential
		
	#输出计算
	marketsWriteIter = gp.UpdateCursor(marketsFeatCls)
	writingMarket = marketsWriteIter.next()
	
	while writingMarket:
		marketId = writingMarket.GetValue(marketsFeatClsOIDFieldName)
		writingMarket.SetValue( "POTENTIAL", marketPotentialDict[marketId] )
		marketsWriteIter.UpdateRow(writingMarket)
		writingMarket = marketsWriteIter.next()
	
	del writingMarket
	del marketsWriteIter