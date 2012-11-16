package mas.io;

import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.charset.Charset;
import java.util.List;

public class ChunkWriter {
	ChunkWriter( RandomAccessFile accessFile ){
		this.accessFile = accessFile;
	}
	
	public Chunk beginChunk( String tag ){
		try{
			assert( tag.length() == 4 );
			assert( isEndOfFile() );
			
			ChunkImpl subchunk = new ChunkImpl(tag, currentChunk);
			if ( currentChunk != null ){
				currentChunk.getSubChunks().add(subchunk);
			}
			
			currentChunk = subchunk;
			currentChunk.setChunkStartPointer( accessFile.getFilePointer() );
			
			// write tag
			writeString(tag, 4);
			// write a place-holder for storage chunk size 
			writeLong(0);
			// write a place-holder for storage sub chunk count
			writeInt(0);
			
		} catch (Exception e){
			e.printStackTrace();
		}
		return currentChunk;
	}
	public void endChunk(){
		// pointer must at the end of the file while seal the chunk.
		try {
			if ( ! this.isEndOfFile() ){
				throw new Exception("File pointer has a incorrect position while end chunk.");
			}

			// write sub chunk pointers
			int chunkCount = currentChunk.getSubChunks().size();
			for (int iChunk = 0; iChunk < chunkCount; ++iChunk){
				writeLong( ((ChunkImpl)currentChunk.getSubChunks().get(iChunk)).getChunkStartPointer() );
			}

			// write current chunk size
			long lastWritePosition = accessFile.getFilePointer();
			accessFile.seek( currentChunk.getChunkStartPointer() + 4/*tag size*/);
			writeLong( lastWritePosition - currentChunk.getChunkStartPointer() );
			writeInt(currentChunk.getSubChunks().size());
			accessFile.seek(lastWritePosition);
			
			// return back to parent chunk
			currentChunk = currentChunk.getParent();
		} catch (Exception e){
			e.printStackTrace();
		}		
	}
	public void endChunk(String tag){
		try {
			if (tag != currentChunk.tag ){
				throw new Exception("current chunk is unmatched!");
			}
			endChunk();
		} catch ( Exception e ){
			e.printStackTrace();
		}
	}
	
	// write scalars
	public void writeByte(int i){
		try{
			accessFile.writeByte( i );
		} catch(Exception e){
			e.printStackTrace();
		}
	}
	public void writeInt(int v ){
		try{
			accessFile.writeInt(v);
		} catch(Exception e){
			e.printStackTrace();
		}
	}
	public void writeLong(long v){
		try{
			accessFile.writeLong(v);
		} catch(Exception e){
			// nothing
		}
	}
	public void writeFloat(float v){
		try{
			accessFile.writeFloat(v);
		} catch(Exception e){
			// nothing
		}
	}
	public void writeDouble(double v){
		try{
			accessFile.writeDouble(v);
		} catch(Exception e){
			e.printStackTrace();
		}
	}
	public void writeString(String v, int len){
		try{
			this.writeFixedLengthString(v, len);
		} catch(Exception e){
			e.printStackTrace();
		}
	}
	public void writeString(String v){
		try {
			accessFile.write(v.getBytes(Charset.forName("utf-8")));
		} catch (Exception e){
			e.printStackTrace();
		}
	}
	public void writeStringWithNullTerminated(String v){
		try{
			writeString(v);
			writeByte(0);
		} catch( Exception e){
			e.printStackTrace();
		}
	}
	
	@SuppressWarnings("unused")
	private void writeFixedLengthString(String content, int bufSize, long startPos) throws IOException{
		accessFile.seek(startPos);
		writeFixedLengthString(content, bufSize);
	}	
	private void writeFixedLengthString(String content, int bufSize) throws IOException{
		byte[] bytes = new byte[bufSize];
		ByteBuffer buf = ByteBuffer.wrap(bytes, 0, bufSize);
		buf.put(content.getBytes(Charset.forName("utf-8")));
		accessFile.write(bytes);
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
	
	private boolean isEndOfFile() throws IOException{
		return accessFile.getFilePointer() == accessFile.length();
	}
	
	private RandomAccessFile accessFile;
	private ChunkImpl currentChunk;
}
