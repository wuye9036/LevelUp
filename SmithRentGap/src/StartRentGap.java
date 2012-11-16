import mas.io.RecordBinaryWriter;
import mas.math.random.ConstantRandomizer;
import mas.math.random.GaussDistributedZone;
import mas.math.random.NormalRandomizer;
import mas.math.random.RandomizeDistributedZone;
import swarm.Globals;

public class StartRentGap {
	public static void main(String[] args) {
		Globals.env.initSwarm("rent gap simulation", "1.0", "wuye9036@gmail.com", args);
		
//		MultiDistribution_Average(3000.0f, 200.0f, 11, 1 );
		MultiDistribution_T(1.0f, 0.5f, 11, 1);
		MultiDistribution_Stddev(100.0f, 50.0f, 11, 1);
		
//		NeighbourRadiusExperiment(1.0f, 0.5f, 6, 20000);
//		NeighbourRadiusExperiment(4.0f, 0.5f, 3, 20000);
//		DeveloperCapitalExperiment( 2000.0f, 100.0f, 10);
//		DeveloperCapitalExperiment( 3000.0f, 100.0f, 10);
//		DeveloperCapitalExperiment( 4000.0f, 100.0f, 10);
//		DeveloperCapitalExperiment( 5000.0f, 100.0f, 10);
//		DeveloperCapitalExperiment( 6000.0f, 100.0f, 10);
//		DeveloperCapitalExperiment( 7000.0f, 100.0f, 10);
//		DeveloperCapitalExperiment( 8000.0f, 100.0f, 10);
//		DeveloperCapitalExperiment( 9000.0f, 100.0f, 10);
//		
//		GapThresholdExperiment(0.4f, 0.05f, 5, 8000);
//		GapThresholdExperiment(0.6f, 0.05f, 7, 8000);
//		
//		PotentialRentExperiment(3000.0f, 200.0f, 10 );
//		DeveloperCapitalExperiment( 2000.0f, 2000.0f, 20);
//		DeveloperCapitalExperiment( 42000.0f, 2000.0f, 20);
		
//		for (int i = 8; i < 25; ++i){
//			if( i == 21 ) continue;
//			MultiDistribution(20, i);
//			System.gc();
//		}
//		MultiSpatialAutocorrectionGenerate(0.1f, 0.1f, 61);
//		RandomSurfaceGenerate(50);
	}
	
	public static void GapThresholdExperiment(float minGap, float step, int batchNumber, float devCap){
		RecordBinaryWriter rbw = new RecordBinaryWriter( "C:\\RGT" + minGap + "_" + step + "_" + batchNumber +"_" + devCap +"DC.serf" );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("Smith租金差距理论试验 - 租金差距阈值");
		for(int i = 0; i < batchNumber; ++i){
			long startTime = System.nanoTime();
			float gap =  minGap + step * i;
			System.out.println("开始第" + (i+1) + "项试验（总" + batchNumber + "项)...");
			RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, "Rent Gap Threshold: " + gap);
			
			//设置参数
			topLevelSwarm.stopTime = 20000;
			topLevelSwarm.model.maintainceThreshold = gap;
			topLevelSwarm.model.developerCapital = devCap;
			topLevelSwarm.model.snapFrequency = 10;
			
			topLevelSwarm.buildObjects();
			topLevelSwarm.buildActions();
			
			topLevelSwarm.activateIn(null);
			topLevelSwarm.go();
			topLevelSwarm.drop();
			
			long endTime = System.nanoTime();
			System.out.println("第" + (i+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
		}
		expRec.endBatch();
	}
	
	public static void DeveloperCapitalExperiment(float minCap, float step, int batchNumber){
		RecordBinaryWriter rbw = new RecordBinaryWriter( "C:\\DC" + minCap + "_" + step + "_" + batchNumber +".serf" );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("Smith租金差距理论试验 - 重建资本");
		for(int i = 0; i < batchNumber; ++i){
			long startTime = System.nanoTime();
			float devCap =  minCap + step * i;
			System.out.println("开始第" + (i+1) + "项试验（总" + batchNumber + "项)...");
			RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, "Developer Capital: " + devCap);
			
			//设置参数
			topLevelSwarm.stopTime = 20000;
			topLevelSwarm.model.developerCapital = devCap;
			topLevelSwarm.model.snapFrequency = 10;
			
			topLevelSwarm.buildObjects();
			topLevelSwarm.buildActions();
			
			topLevelSwarm.activateIn(null);
			topLevelSwarm.go();
			topLevelSwarm.drop();
			
			long endTime = System.nanoTime();
			System.out.println("第" + (i+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
		}
		expRec.endBatch();
	}
	
	public static void NeighbourRadiusExperiment(
			float minRadius,
			float step, 
			int batchNumber,
			int stopTime){
		RecordBinaryWriter rbw = new RecordBinaryWriter( "C:\\NR_" + minRadius + "_" + step + "_" + batchNumber + "_" + stopTime +"ST.serf" );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("Smith租金差距理论试验 - 邻近平均租金计算半径");
		for(int i = 0; i < batchNumber; ++i){
			long startTime = System.nanoTime();
			float neighbourRadius =  minRadius + step * i;
			System.out.println("开始第" + (i+1) + "项试验（总" + batchNumber + "项)...");
			RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, "Neighbour Radius: " + neighbourRadius);
			
			//设置参数
			topLevelSwarm.stopTime = stopTime;
			topLevelSwarm.model.neighbourRadius = neighbourRadius;
			topLevelSwarm.model.snapFrequency = 10;
			
			topLevelSwarm.buildObjects();
			topLevelSwarm.buildActions();
			
			topLevelSwarm.activateIn(null);
			topLevelSwarm.go();
			topLevelSwarm.drop();
			
			long endTime = System.nanoTime();
			System.out.println("第" + (i+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
		}
		expRec.endBatch();
	}

	public static void PotentialRentExperiment(float minPR, float step, int batchNumber){
		RecordBinaryWriter rbw = new RecordBinaryWriter( String.format("C:\\PR_%f_%f_%d.serf", minPR, step, batchNumber) );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("Smith租金差距理论试验 - 潜在地租");
		for(int i = 0; i < batchNumber; ++i){
			long startTime = System.nanoTime();
			float curPr =  minPR + step * i;
			System.out.println("开始第" + (i+1) + "项试验（总" + batchNumber + "项)...");
			RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, "Potential Rent: " + curPr);
			
			//设置参数
			topLevelSwarm.stopTime = 20000;
			topLevelSwarm.model.potentialRentGen = new RandomizeDistributedZone( new ConstantRandomizer(curPr), topLevelSwarm.model.worldSize, topLevelSwarm.model.worldSize );
			topLevelSwarm.model.snapFrequency = 10;
			
			topLevelSwarm.buildObjects();
			topLevelSwarm.buildActions();
			
			topLevelSwarm.activateIn(null);
			topLevelSwarm.go();
			topLevelSwarm.drop();
			
			long endTime = System.nanoTime();
			System.out.println("第" + (i+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
		}
		expRec.endBatch();
	}
	
	public static void Test(){
		RecordBinaryWriter rbw = new RecordBinaryWriter( "C:\\Test2.serf" );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("这是一个测试实验，用于验证程序正确性。");
		int batchNumber = 5;
		for(int i = 0; i < batchNumber; ++i){
			long startTime = System.nanoTime();
			System.out.println("开始第" + (i+1) + "项试验（总" + batchNumber + "项)...");
			RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, "Test: " + i);
			
			//设置参数
			topLevelSwarm.stopTime = 200;
			topLevelSwarm.model.neighbourRadius = 1.5f;
			topLevelSwarm.model.snapFrequency = 20;
			topLevelSwarm.model.potentialRentGen = new GaussDistributedZone(topLevelSwarm.model.worldSize, topLevelSwarm.model.worldSize, 3000, 200.0, 9, 5.0);
			
			topLevelSwarm.buildObjects();
			topLevelSwarm.buildActions();
			
			topLevelSwarm.activateIn(null);
			topLevelSwarm.go();
			topLevelSwarm.drop();
			
			long endTime = System.nanoTime();
			System.out.println("第" + (i+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
		}
		expRec.endBatch();
	}
	
	public static void MultiDistribution(int batchNumber, int batchId){
		RecordBinaryWriter rbw = new RecordBinaryWriter( "C:\\MD_" + batchId + ".serf" );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("同一分布的多次重复试验。");
		for(int i = 0; i < batchNumber; ++i){
			long startTime = System.nanoTime();
			System.out.println("开始第" + (i+batchId*batchNumber+1) + "项试验（总" + batchNumber*batchId + "项)...");
			RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, "Experiment: " + i);
			
			//设置参数
			topLevelSwarm.stopTime = 20000;
			topLevelSwarm.model.neighbourRadius = 1.5f;
			topLevelSwarm.model.snapFrequency = 10;
			topLevelSwarm.model.potentialRentGen = new GaussDistributedZone(topLevelSwarm.model.worldSize, topLevelSwarm.model.worldSize, 3000, 1000.0, 9, 5.0);
			
			topLevelSwarm.buildObjects();
			topLevelSwarm.buildActions();
			
			topLevelSwarm.activateIn(null);
			topLevelSwarm.go();
			topLevelSwarm.drop();
			
			long endTime = System.nanoTime();
			System.gc();
			System.out.println("第" + (i+batchId*batchNumber+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
		}
		expRec.endBatch();
	}
	
	public static void MultiDistribution_Average(float minAvg, float step, int batchNumber, int innerBatchNumber ){
		RecordBinaryWriter rbw = new RecordBinaryWriter( String.format("C:\\MD_A_%f_%f_%d_B%d.serf", minAvg, step, batchNumber, innerBatchNumber) );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("不同平均值的自相关分布的试验。每个试验重复做数次");
		for(int i = 0; i < batchNumber; ++i){
			float curAvg = minAvg + (i*step);
			for( int j = 0; j < innerBatchNumber; ++j){
				long startTime = System.nanoTime();
				System.out.println("开始第" + (i*innerBatchNumber+j+1) + "项试验（总" + batchNumber*innerBatchNumber + "项)...");
				RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, String.format("Experiment: %d at %f", j, curAvg) );
				
				//设置参数
				topLevelSwarm.stopTime = 20000;
				topLevelSwarm.model.neighbourRadius = 1.5f;
				topLevelSwarm.model.snapFrequency = 10;
				GaussDistributedZone gdz = new GaussDistributedZone(topLevelSwarm.model.worldSize, topLevelSwarm.model.worldSize, curAvg, 500.0, 15, 5.0);
				while ( Math.abs(gdz.getAverage() - curAvg) > step / 10.0
						|| gdz.getMin() < 1000.0
						|| Math.abs(gdz.getStandardDev() - 500.0) > 50.0
						){
					gdz.regenerate();
				}
				topLevelSwarm.model.potentialRentGen = gdz; 
				
				topLevelSwarm.buildObjects();
				topLevelSwarm.buildActions();
				
				topLevelSwarm.activateIn(null);
				topLevelSwarm.go();
				topLevelSwarm.drop();
				
				long endTime = System.nanoTime();
				System.out.println("第" + (i*innerBatchNumber+j+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
			}
		}
		expRec.endBatch();
	}
	
	public static void MultiDistribution_T(float minT, float step, int batchNumber, int innerBatchNumber ){
		RecordBinaryWriter rbw = new RecordBinaryWriter( String.format("C:\\MD_T_%f_%f_%d_B%d.serf", minT, step, batchNumber, innerBatchNumber) );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("不同T值的自相关分布的试验。每个平均值做数次");
		for(int i = 0; i < batchNumber; ++i){
			float curT = minT + (i*step);
			for( int j = 0; j < innerBatchNumber; ++j){
				long startTime = System.nanoTime();
				System.out.println("开始第" + (i*innerBatchNumber+j+1) + "项试验（总" + batchNumber*innerBatchNumber + "项)...");
				RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, String.format("Experiment: %d at %f", j, curT) );
				
				//设置参数
				topLevelSwarm.stopTime = 20000;
				topLevelSwarm.model.neighbourRadius = 1.5f;
				topLevelSwarm.model.snapFrequency = 10;
				
				GaussDistributedZone gdz = new GaussDistributedZone(topLevelSwarm.model.worldSize, topLevelSwarm.model.worldSize, 3000.0, 500.0, 15, curT);
				while ( Math.abs(gdz.getAverage() - 3000.0) > 100.0
						|| gdz.getMin() < 1000.0
						|| Math.abs(gdz.getStandardDev() - 500.0) > 25.0
						){
					gdz.regenerate();
				}
				topLevelSwarm.model.potentialRentGen = gdz; 				
				
				topLevelSwarm.buildObjects();
				topLevelSwarm.buildActions();
				
				topLevelSwarm.activateIn(null);
				topLevelSwarm.go();
				topLevelSwarm.drop();
				
				long endTime = System.nanoTime();
				System.out.println("第" + (i*innerBatchNumber+j+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
			}
		}
		expRec.endBatch();
	}
	
	public static void MultiDistribution_Stddev(float minSD, float step, int batchNumber, int innerBatchNumber ){
		RecordBinaryWriter rbw = new RecordBinaryWriter( String.format("C:\\MD_SD_%f_%f_%d_B%d.serf", minSD, step, batchNumber, innerBatchNumber) );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("不同标准差的自相关分布的试验。每个试验重复做数次");
		for(int i = 0; i < batchNumber; ++i){
			float curSD = minSD + (i*step);
			for( int j = 0; j < innerBatchNumber; ++j){
				long startTime = System.nanoTime();
				System.out.println("开始第" + (i*innerBatchNumber+j+1) + "项试验（总" + batchNumber*innerBatchNumber + "项)...");
				RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, String.format("Experiment: %d at %f", j, curSD) );
				
				//设置参数
				topLevelSwarm.stopTime = 20000;
				topLevelSwarm.model.neighbourRadius = 1.5f;
				topLevelSwarm.model.snapFrequency = 10;
				
				GaussDistributedZone gdz = new GaussDistributedZone(topLevelSwarm.model.worldSize, topLevelSwarm.model.worldSize, 3000.0, curSD, 15, 5.0);
				while ( Math.abs(gdz.getAverage() - 3000.0) > 100.0
						|| gdz.getMin() < 1000.0
						|| Math.abs(gdz.getStandardDev() - curSD) > step / 20.0f
						){
					gdz.regenerate();
				}
				topLevelSwarm.model.potentialRentGen = gdz; 	
				
				topLevelSwarm.buildObjects();
				topLevelSwarm.buildActions();
				
				topLevelSwarm.activateIn(null);
				topLevelSwarm.go();
				topLevelSwarm.drop();
				
				long endTime = System.nanoTime();
				System.out.println("第" + (i*innerBatchNumber+j+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
			}
		}
		expRec.endBatch();
	}
	
	public static void MultiSpatialAutocorrectionGenerate(float minT, float step, int batchNumber ){
		RecordBinaryWriter rbw = new RecordBinaryWriter( String.format("C:\\MSA5_%f_%f_%d.serf", minT, step, batchNumber) );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("以不同的相关距离T创建空间自相关分布的表面。");
		for(int i = 0; i < batchNumber; ++i){
			float curT = minT + (i*step);
			long startTime = System.nanoTime();
			System.out.println("开始第" + (i+1) + "项试验（总" + batchNumber + "项)...");
			RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, String.format("T_%f", curT) );
			
			//设置参数
			topLevelSwarm.stopTime = 1;
			topLevelSwarm.model.neighbourRadius = 1.5f;
			topLevelSwarm.model.snapFrequency = 10;
			topLevelSwarm.model.potentialRentGen = new GaussDistributedZone(topLevelSwarm.model.worldSize, topLevelSwarm.model.worldSize, 3000.0, 500.0, 15, curT);
			
			topLevelSwarm.buildObjects();
			topLevelSwarm.buildActions();
			
			topLevelSwarm.activateIn(null);
			topLevelSwarm.go();
			topLevelSwarm.drop();
			
			long endTime = System.nanoTime();
			System.out.println("第" + (i+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
		}
		expRec.endBatch();
	}
	
	public static void RandomSurfaceGenerate(int batchNumber ){
		RecordBinaryWriter rbw = new RecordBinaryWriter( String.format("C:\\ND_%d.serf", batchNumber) );
		ExperimentRecorder expRec = new ExperimentRecorder(rbw);
		
		expRec.beginBatch("产生多组数值成Normal分布的Distribution。");
		for(int i = 0; i < batchNumber; ++i){
			long startTime = System.nanoTime();
			System.out.println("开始第" + (i+1) + "项试验（总" + batchNumber + "项)...");
			RentGapBatchSwarm topLevelSwarm = new RentGapBatchSwarm(Globals.env.globalZone, expRec, String.format("EXPID_%d", i) );
			
			//设置参数
			topLevelSwarm.stopTime = 1;
			topLevelSwarm.model.neighbourRadius = 1.5f;
			topLevelSwarm.model.snapFrequency = 10;
			topLevelSwarm.model.potentialRentGen = new RandomizeDistributedZone( new NormalRandomizer(0.0, 1.0), topLevelSwarm.model.worldSize, topLevelSwarm.model.worldSize);
			
			topLevelSwarm.buildObjects();
			topLevelSwarm.buildActions();
			
			topLevelSwarm.activateIn(null);
			topLevelSwarm.go();
			topLevelSwarm.drop();
			
			long endTime = System.nanoTime();
			System.out.println("第" + (i+1) + "项试验完成。用时" + (double)(endTime - startTime) / 1.0e9 + "秒");
		}
		expRec.endBatch();
	}
}
