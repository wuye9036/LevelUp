package mas.io;

public class RecordItemFormatDescription {
	public static RecordItemFormatDescription create(
			RecordItemIOType ioType,
			RecordItemDataDimension itemType,
			String name,
			RecordItemDataType itemDataType,
			boolean isTimeSeries,
			long[] size
			){
		
		RecordItemFormatDescription ret = new RecordItemFormatDescription();
		ret.ioType = ioType;
		ret.itemType = itemType;
		ret.itemName = name;
		ret.itemDataType = itemDataType;
		ret.isTimeSeries = isTimeSeries;
		if(size != null){
			ret.size = size.clone();
		} else {
			ret.size = new long[4];
		}
		return ret;
	}
	
	public RecordItemIOType ioType;
	public RecordItemDataDimension itemType;
	public String itemName;
	public RecordItemDataType itemDataType;
	public boolean isTimeSeries;
	public long[] size;
}
