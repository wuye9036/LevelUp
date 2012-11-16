import java.io.*;
import java.util.*;
import java.util.ArrayList;
import mas.io.RecordBinaryWriter;
import mas.io.RecordItemDataType;
import mas.io.RecordItemFormatDescription;
import mas.io.RecordItemIOType;
import mas.io.RecordItemDataDimension;
import mas.math.vector.Grid2DPosition;

public class ExperimentRecorder {
	public RentGapModelSwarm model;
	private RecordBinaryWriter rbw;
	private int timeStamp = 0;
	FileOutputStream f;
	Writer out;  

	public ExperimentRecorder( RecordBinaryWriter rbw){
		this.rbw = rbw;
	}
	
	public void beginBatch(String batchName){
		System.out.println( "开始实验组：" + batchName );
		rbw.beginBatch(batchName);
		try {
			f= new FileOutputStream("C:\\1.csv", false);
			out = new OutputStreamWriter(f);  
		} catch (Exception e) {
			e.printStackTrace();
		}
		
		ArrayList<RecordItemFormatDescription> itemFmts = new ArrayList<RecordItemFormatDescription>();
		
		long[] snapSize = new long[]{41, 41, 0, 0};
		
		itemFmts.add(RecordItemFormatDescription.create(RecordItemIOType.input, RecordItemDataDimension.scalar, "Construction Cost", RecordItemDataType._float, false, null));
		itemFmts.add(RecordItemFormatDescription.create(RecordItemIOType.input, RecordItemDataDimension.scalar, "Developer Capital", RecordItemDataType._float, false, null));
		itemFmts.add(RecordItemFormatDescription.create(RecordItemIOType.input, RecordItemDataDimension.scalar, "Maintaince Threshold", RecordItemDataType._float, false, null));
		itemFmts.add(RecordItemFormatDescription.create(RecordItemIOType.input, RecordItemDataDimension.scalar, "World Size", RecordItemDataType._int, false, null));
		itemFmts.add(RecordItemFormatDescription.create(RecordItemIOType.input, RecordItemDataDimension.scalar, "Neighbour Radius", RecordItemDataType._float, false, null));
		itemFmts.add(RecordItemFormatDescription.create(RecordItemIOType.input, RecordItemDataDimension._2D, "Potential Rent", RecordItemDataType._float, false, snapSize));
		
		itemFmts.add(RecordItemFormatDescription.create(RecordItemIOType.output, RecordItemDataDimension.scalar, "Average Captial Rent", RecordItemDataType._float, true, null));
		itemFmts.add(RecordItemFormatDescription.create(RecordItemIOType.output, RecordItemDataDimension._2D, "Environment Snap Shot", RecordItemDataType._float, true, snapSize));
		
		rbw.writeRecordItemFormatArray(itemFmts.toArray(new RecordItemFormatDescription[0]));
	}
	
	public void endBatch(){
		try {
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		try {
			f.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		System.out.println( "结束实验组。" );
		rbw.endBatch();
	}
	
	public void beginExperiment(RentGapModelSwarm model, String experimentName){
		System.out.println( "Begin at: " + (new Date()).toString() );
		rbw.beginExperiment(experimentName);
		this.model = model;
		timeStamp = 0;
		
		rbw.beginNonTimeSeriesData();
		
		rbw.writeFloat(model.constructionCost);
		rbw.writeFloat(model.developerCapital);
		rbw.writeFloat(model.maintainceThreshold);
		rbw.writeInt(model.worldSize);
		rbw.writeFloat(model.neighbourRadius);
		for( int ix = 0; ix < model.worldSize; ++ix ){
			for( int iy = 0; iy < model.worldSize; ++iy ){
				rbw.writeFloat(model.area.getPropertyUnit(new Grid2DPosition(ix, iy)).potentialRent);
			}
		}
		
		rbw.endNonTimeSeriesData();
	}
	
	public void endExperiment(){
		rbw.endExperiment();
	}
	
	public void update()
	{
		try {
			rbw.beginTimeStamp(timeStamp, 0);
			rbw.writeFloat(model.area.getACR());
			rbw.endTimeStamp();
			
			if ( timeStamp % model.snapFrequency == 0 && timeStamp > 19000 ){
				rbw.beginTimeStamp(timeStamp, 1);
				for(int ix = 0; ix < model.area.width; ++ix){
					for(int iy = 0; iy < model.area.height; ++iy){
						rbw.writeFloat(model.area.getPropertyUnit(ix, iy).capitalRent);
					}
				}
				rbw.endTimeStamp();
			}
			
			++timeStamp;
		} catch (Exception e) {
			e.printStackTrace();
		}
		
	}
}
