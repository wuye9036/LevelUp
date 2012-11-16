package mas.io;

import java.io.*;
import java.util.*;

public class RecordBinaryWriter {
	public RecordBinaryWriter(String filePath){
		try{
			File f = new File( filePath );
			if(f.exists()){f.delete();}
			accessFile = new RandomAccessFile( filePath ,"rw" );
			chunkWriter = new ChunkWriter( accessFile );
		} catch ( Exception e ){
			e.printStackTrace();
		}
	}
	
	public void beginBatch( String batchDesc ){
		chunkWriter.beginChunk("SERF");
		
		chunkWriter.beginChunk("DESC");
		chunkWriter.writeString(batchDesc);
		chunkWriter.endChunk("DESC");
	}
	public void endBatch() {
		try {
			chunkWriter.endChunk("SERF");
			accessFile.close();
		} catch (Exception e){
		}
	}

	public void writeRecordItemFormatArray(RecordItemFormatDescription[] itemFmts){
		try{
			chunkWriter.beginChunk("RIFD");
			for( int iItemFmts = 0; iItemFmts < itemFmts.length; ++iItemFmts){
				writeRecordItemFormat(itemFmts[iItemFmts]);
			}
			chunkWriter.endChunk("RIFD");
		} catch(Exception e) {
			e.printStackTrace();
		}
	}
	
	public void beginExperiment( String expName ){
		try{
			chunkWriter.beginChunk("EXPR");
			chunkWriter.beginChunk("DESC");
			chunkWriter.writeString(expName);
			chunkWriter.endChunk("DESC");
		} catch( Exception e){
			e.printStackTrace();
		}
	}
	public void endExperiment() {
		try{
			chunkWriter.endChunk("EXPR");
		} catch( Exception e ){
			e.printStackTrace();
		}
	}
	
	public void beginNonTimeSeriesData(){
		chunkWriter.beginChunk("NTSD");
	}
	public void endNonTimeSeriesData(){
		chunkWriter.endChunk("NTSD");
	}
	
	public void beginTimeStamp(int timeStamp, int recId){
		try{
			chunkWriter.beginChunk("TIME");
			writeInt(timeStamp);
			writeInt(recId);
		} catch (Exception e){
			e.printStackTrace();
		}
	}
	public void endTimeStamp(){
		chunkWriter.endChunk("TIME");
	}
	
	// write scalars
	public void writeInt(int v ){
		chunkWriter.writeInt(v);
	}
	public void writeLong(long v){
		chunkWriter.writeLong(v);
	}
	public void writeFloat(float v){
		chunkWriter.writeFloat(v);
	}
	public void writeDouble(double v){
		chunkWriter.writeDouble(v);
	}
	public void writeString(String v, int len){
		chunkWriter.writeString(v, len);
	}
	
	// write null-terminated string
	public void writeStringNT(String v){
		chunkWriter.writeStringWithNullTerminated(v);
	}
	
	// write list/matrix
	public void writeIntList(List<Integer> v){
		for( int i = 0; i < v.size(); ++i){
			writeInt(v.get(i));
		}
	}
	public void writeLongList(List<Long> v){
		for( int i = 0; i < v.size(); ++i){
			writeLong(v.get(i));
		}
	}
	public void writeFloatList(List<Float> v){
		for( int i = 0; i < v.size(); ++i){
			writeFloat(v.get(i));
		}
	}
	public void writeDoubleList(List<Double> v){
		for( int i = 0; i < v.size(); ++i){
			writeDouble(v.get(i));
		}
	}

	private void writeRecordItemFormat(RecordItemFormatDescription itemFmt) throws IOException{
		String ioTypeStr = "";
		String typeStr = "";
		String dataTypeStr = "";
		
		switch( itemFmt.ioType ){
		case input:
			ioTypeStr = "I";
			break;
		case output:
			ioTypeStr = "O";
			break;
		}
		
		switch( itemFmt.itemType ){
		case scalar:
			typeStr = "SV";
			break;
		case _1D:
			typeStr = "1D";
			break;
		case _2D:
			typeStr = "2D";
			break;
		}
		
		if (itemFmt.isTimeSeries){
			typeStr += "T";
		}
		
		switch( itemFmt.itemDataType ){
		case _int:
			dataTypeStr = "int";
			break;
		case _float:
			dataTypeStr = "float";
			break;
		case _double:
			dataTypeStr = "double";
			break;
		case _string:
			dataTypeStr = "string";
			break;
		}
		
		writeString(ioTypeStr, 1);
		writeString(typeStr, 4);
		writeStringNT(itemFmt.itemName);
		writeString(dataTypeStr, 8);
		
		for(int i = 0; i < 4; ++i){
			writeLong(itemFmt.size[i]);
		}
	}
	
	private RandomAccessFile accessFile;
	private ChunkWriter chunkWriter;
}
