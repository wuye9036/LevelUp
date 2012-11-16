using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace SwarmExperimentalAnalyser.Model.ChunkIO {
	class ChunkImpl : Chunk {
		public ChunkImpl(ChunkReader reader) {
			this.reader = reader;
		}

		#region "Inherited"
		public override string Tag {
			get { return tag; }
		}
		public override bool IsLeaf {
			get {
				Fill();
				return subChunksCount == 0; 
			}
		}
		public override List<Chunk> this[string subChunkName] {
			get {
				Fill();
				if (!subChunks.ContainsKey(subChunkName)) {
					subChunks[subChunkName] = new List<Chunk>();
				}
				return subChunks[subChunkName];
			}
		}
		public override List<string> SubchunkTags {
			get {
				Fill();
				return new List<string>(subChunks.Keys);
			}
		}
		public override byte[] ChunkBytes {
			get {
				Fill();
				return chunkContentBytes;
			}
		}
		public override byte[] ReadChunkBytes(long offset, long length) {
			return reader.ReadChunkBytes(this, offset, length);
		}
		public override void Release() {
			chunkContentBytes = null;
			subChunks = new Dictionary<string, List<Chunk>>();
			isAvaliable = false;
			GC.Collect();
		}

		protected void Fill() {
			if (isAvaliable) {
				return;
			}

			reader.FillChunk(this);
			isAvaliable = true;
		}
		#endregion

		#region "Size Information"
		public long ChunkSize {
			get { return chunkSize; }
			set { chunkSize = value; }
		}
		public long SubchunksCount {
			get { return subChunksCount; }
			set { subChunksCount = value; }
		}
		public long SubchunkPointerArraySize {
			get { return SubchunksCount * ChunkPointerSize; }
		}
		public long ContentSize {
			get { return ChunkSize - TagSize - ChunkSizeSize - SubchunksCountSize - SubchunkPointerArraySize; }
		}
		#endregion

		#region "Location Information"
		public long ChunkStartPointer {
			get { return chunkStartPointer; }
			set { chunkStartPointer = value; }
		}
		public long ChunkTagPointer {
			get { return ChunkStartPointer; }
		}
		public long ChunkSizePointer {
			get { return ChunkStartPointer + TagSize; }
		}
		public long SubchunksCountPointer {
			get { return ChunkSizePointer + ChunkSizeSize; }
		}
		public long ChunkContentPointer {
			get { return SubchunksCountPointer + SubchunksCountSize; }
		}
		public long SubchunkPointersPointer {
			get { return ChunkStartPointer + ChunkSize - SubchunkPointerArraySize; }
		}
		#endregion

		public void SetTag(string tag) {
			this.tag = tag;
		}
		public void SetChunkBytes(byte[] chunkBytes) {
			chunkContentBytes = chunkBytes;
		}
		public bool IsAvaliable {
			get { return isAvaliable; }
			set { isAvaliable = value; }
		}
		public void AddSubchunk(ChunkImpl chunk) {
			if (!subChunks.ContainsKey(chunk.tag)) {
				subChunks.Add(chunk.tag, new List<Chunk>(new ChunkImpl[] { chunk }));
			} else {
				subChunks[chunk.tag].Add(chunk);
			}
		}

		public const long TagSize = 4;
		public const long ChunkSizeSize = 8;
		public const long SubchunksCountSize = 4;
		public const long ChunkPointerSize = 8;

		private bool isAvaliable = false;
		private ChunkReader reader;

		protected byte[] chunkContentBytes;
		protected long subChunksCount;
		protected Dictionary<string, List<Chunk>> subChunks = new Dictionary<string, List<Chunk>>();

		protected string tag;
		protected long chunkSize;
		protected long chunkStartPointer;
	}

	class ChunkReader {
		public ChunkReader(string fileName) {
			this.chunkFile = new FileStream(fileName, FileMode.Open);	
		}

		public ChunkReader(FileStream chunkFile) {
			this.chunkFile = chunkFile;
		}

		public Chunk RootChunk {
			get { return AllocateChunk(0); }
		}

		public void FillChunk(Chunk chunk) {
			ChunkImpl derivedChunk = chunk as ChunkImpl;
			FillSubchunks(derivedChunk);
			FillChunkBytes(derivedChunk);
			derivedChunk.IsAvaliable = true;
		}

		public byte[] ReadChunkBytes(ChunkImpl chunk, long offset, long length) {
			if (length == -1) {
				length = chunk.ContentSize - offset;
			}
			return ReadBytes(chunk.ChunkContentPointer + offset, length);
		}

		#region "Chunk Hi-Level IO"
		private ChunkImpl AllocateChunk(long chunkPointer) {
			ChunkImpl retChunk = new ChunkImpl(this);
			retChunk.ChunkStartPointer = chunkPointer;
			FillChunkTag(retChunk);
			FillChunkSize(retChunk);
			return retChunk;
		}

		private void FillChunkTag(ChunkImpl chunk) {
			chunk.SetTag(BytesToString(ReadBytes(chunk.ChunkTagPointer, ChunkImpl.TagSize)));
		}

		private void FillChunkSize(ChunkImpl chunk) {
			chunk.ChunkSize = BigEndianBytesToInt64(ReadBytes(chunk.ChunkSizePointer, ChunkImpl.ChunkSizeSize), 0);
		}

		private void FillSubchunksCount(ChunkImpl chunk) {
			chunk.SubchunksCount = BigEndianBytesToInt32(ReadBytes(chunk.SubchunksCountPointer, ChunkImpl.SubchunksCountSize), 0);
		}
		private void FillSubchunks(ChunkImpl chunk) {
			FillSubchunksCount(chunk);
			byte[] subchunkPointerBytes = ReadBytes(chunk.SubchunkPointersPointer, chunk.SubchunkPointerArraySize);
			for (int iSubchunk = 0; iSubchunk < chunk.SubchunksCount; ++iSubchunk) {
				long chunkPointer = BigEndianBytesToInt64( subchunkPointerBytes, (int)(iSubchunk * ChunkImpl.ChunkPointerSize) );
				ChunkImpl subchunk = AllocateChunk(chunkPointer);
				chunk.AddSubchunk(subchunk);
			}
		}

		private void FillChunkBytes(ChunkImpl chunk) {
			if (chunk.SubchunksCount == 0) {
				chunk.SetChunkBytes( ReadBytes(chunk.ChunkContentPointer, chunk.ContentSize) );
			}
		}

		#endregion

		#region "Chunk Low Level IO"
		byte[] ReadBytes( long size ) {
			byte[] retBytes = new byte[(int)size];
			chunkFile.Read(retBytes, 0, (int)size);
			return retBytes;
		}

		byte[] ReadBytes(long startPos, long size) {
			chunkFile.Seek(startPos, SeekOrigin.Begin);
			return ReadBytes(size);
		}
		#endregion

		#region "Type Conversation"
		static public string BytesToString(byte[] b) {
			return Encoding.UTF8.GetString(b).TrimEnd('\0');
		}
		static public string NullTerminatedBytesToString(byte[] b, int start, ref int end) {
			for ( end = start; b[end] != 0; ++end) {
				if (end == b.Length) {
					break;
				}
			}
			end = Math.Min(end+1, b.Length);
			return BytesToString(b, start, end - start);
		}
		static public string BytesToString(byte[] b, int start, int len) {
			return Encoding.UTF8.GetString(b, start, len).TrimEnd('\0');
		}
		static public int BigEndianBytesToInt32(byte[] b, int startIndex) {
			byte[] subBytes = new byte[4];
			Array.Copy(b, startIndex, subBytes, 0, 4);
			if (BitConverter.IsLittleEndian) {
				Array.Reverse(subBytes);
			}
			return BitConverter.ToInt32(subBytes, 0);
		}
		static public long BigEndianBytesToInt64(byte[] b, int startIndex) {
			byte[] subBytes = new byte[8];
			Array.Copy(b, startIndex, subBytes, 0, 8);
			if (BitConverter.IsLittleEndian) {
				Array.Reverse(subBytes);
			}
			return BitConverter.ToInt64(subBytes, 0);
		}
		static public float BigEndianBytesToFloat(byte[] b, int startIndex) {
			byte[] subBytes = new byte[4];
			Array.Copy(b, startIndex, subBytes, 0, 4);
			if (BitConverter.IsLittleEndian) {
				Array.Reverse(subBytes);
			}
			return BitConverter.ToSingle(subBytes, 0);
		}
		static public double BigEndianBytesToDouble(byte[] b, int startIndex) {
			byte[] subBytes = new byte[8];
			Array.Copy(b, startIndex, subBytes, 0, 8);
			if (BitConverter.IsLittleEndian) {
				Array.Reverse(subBytes);
			}
			return BitConverter.ToDouble(subBytes, 0);
		}
		static public object BigEndianBytesToObject(byte[] b, int startIndex, Type t) {
			if (b == null) {
				return null;
			}
			if (t == typeof(int)) {
				return (object)BigEndianBytesToInt32(b, startIndex);
			} else if (t == typeof(long)) {
				return (object)BigEndianBytesToInt64(b, startIndex);
			} else if (t == typeof(float)) {
				return (object)BigEndianBytesToFloat(b, startIndex);
			} else if (t == typeof(double)) {
				return (object)BigEndianBytesToDouble(b, startIndex);
			} else if (t == typeof(string)) {
				return (object)BytesToString(b);
			}
			return null;
		}
		#endregion

		private FileStream chunkFile;
	}
}
