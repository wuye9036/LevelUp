using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.IO;
using System.Security.Cryptography;

using System.Xml;

namespace Backuper
{
	public partial class Backuper : Form
	{
		private string FileSizeToString(long size)
		{
			double K = 1024.0;
			double M = K * K;
			double G = K * M;

			double dSize = (double)size;

			if (dSize > G)
			{
				return string.Format("{0:F}", dSize / G) + " GB";
			}
			if (dSize > M)
			{
				return string.Format("{0:F}", dSize / M) + " MB";
			}
			if (dSize > K)
			{
				return string.Format("{0:F}", dSize / K) + " KB";
			}
			return size.ToString() + " Bytes";
		}

		private void ShowInfo()
		{
			PathNode currentPathNode = currentNode_.Tag as PathNode;
			if (currentPathNode.IsDirectory)
			{
				MessageBox.Show(
					string.Format("树路径：{0}\n实际路径：{1}\n",
							currentNode_.FullPath,
							currentPathNode.FullName
						)
					);
			}
			else
			{
				MessageBox.Show(
					string.Format("树路径:{0}\n实际路径：{1}\n文件大小:{2}\n最后更新：{3}\n效验和：{4}\n",
							currentNode_.FullPath,
							currentPathNode.FullName,
							FileSizeToString(currentPathNode.Size),
							currentPathNode.LastWriteTime,
							currentPathNode.Checksum
						)
					);
			}
		}

		public Backuper()
		{
			InitializeComponent();
		}

		private void Backuper_Load(object sender, EventArgs e)
		{
			cmpTree_ = new ComparisonTree(ltv, rtv, cmsTreeItem);
		}

		private ComparisonTree cmpTree_;

		private void openLeftToolStripMenuItem_Click(object sender, EventArgs e)
		{
			FolderBrowserDialog fbd = new FolderBrowserDialog();
			fbd.ShowNewFolderButton = false;
			fbd.ShowDialog();
		}

		private void exitToolStripMenuItem_Click(object sender, EventArgs e)
		{
			this.Close();
		}

		private void tsmiAddFolder_Click(object sender, EventArgs e)
		{
			//获得右键菜单的所在节点
			ToolStripMenuItem menuItem = sender as ToolStripMenuItem;
			TreeNode node = menuItem.Owner.Tag as TreeNode;

			//打开目录选择对话框
			FolderBrowserDialog fbd = new FolderBrowserDialog();
			fbd.ShowNewFolderButton = false;


			//获取目录并开始添加到目录树当中
			if (fbd.ShowDialog() == DialogResult.OK)
			{
				Cursor oldCursor = Cursor;
				Cursor = Cursors.WaitCursor;
				if (menuItem == tsmiAddFolderShallow)
				{
					cmpTree_.Add(fbd.SelectedPath, node, false);
				}
				else
				{
					cmpTree_.Add(fbd.SelectedPath, node, true);
				}
				Cursor = oldCursor;
			}
		}

		private void tv_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
		{
			e.Node.TreeView.SelectedNode = e.Node;
			if (e.Button != MouseButtons.Right)
			{
				currentNode_ = e.Node;
				return;
			}

			cmsTreeItem.Tag = e.Node;
			cmsTreeItem.Show(e.Node.TreeView.PointToScreen(e.Location));
		}

		private void tmsiDelete_Click(object sender, EventArgs e)
		{
			//获得右键菜单的所在节点
			ToolStripMenuItem menuItem = sender as ToolStripMenuItem;
			TreeNode node = menuItem.Owner.Tag as TreeNode;

			//根节点没法删除
			if (node == node.TreeView.Nodes[0])
			{
				return;
			}

			node.Remove();
			(node.Tag as PathNode).Remove();
		}

		private void tsbRefresh_Click(object sender, EventArgs e)
		{
			Cursor oldCursor = Cursor;
			Cursor = Cursors.WaitCursor;
			cmpTree_.Compare();
			cmpTree_.Refresh();
			Cursor = oldCursor;
		}

		private void tsmiDeleteAllSub_Click(object sender, EventArgs e)
		{
			//获得右键菜单的所在节点
			ToolStripMenuItem menuItem = sender as ToolStripMenuItem;
			TreeNode node = menuItem.Owner.Tag as TreeNode;

			node.Nodes.Clear();
			(node.Tag as PathNode).Clear();
		}

		private void tsmiAddFiles_Click(object sender, EventArgs e)
		{
			//获得右键菜单的所在节点
			ToolStripMenuItem menuItem = sender as ToolStripMenuItem;
			TreeNode node = menuItem.Owner.Tag as TreeNode;

			//打开文件选择对话框
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Multiselect = true;
			if (ofd.ShowDialog() == DialogResult.OK)
			{
				foreach (string filePath in ofd.FileNames)
				{
					cmpTree_.AddAsSub(filePath, node, false);
				}
			}
		}

		private void tsmiAddFolderAsSub_Click(object sender, EventArgs e)
		{
			//获得右键菜单的所在节点
			ToolStripMenuItem menuItem = sender as ToolStripMenuItem;
			TreeNode node = menuItem.Owner.Tag as TreeNode;

			//打开目录选择对话框
			FolderBrowserDialog fbd = new FolderBrowserDialog();
			fbd.ShowNewFolderButton = false;


			//获取目录并开始添加到目录树当中
			if (fbd.ShowDialog() == DialogResult.OK)
			{
				Cursor oldCursor = Cursor;
				Cursor = Cursors.WaitCursor;
				if (menuItem == tsmiAddFolderAsSub)
				{
					cmpTree_.AddAsSub(fbd.SelectedPath, node, false);
				}
				else
				{
					cmpTree_.AddAsSub(fbd.SelectedPath, node, true);
				}
				Cursor = oldCursor;
			}
		}

		private void tsbSave_Click(object sender, EventArgs e)
		{
			SaveOption saveOptionWnd = new SaveOption();
			saveOptionWnd.ShowDialog();
			if (saveOptionWnd.IsOK)
			{
				string fileName = saveOptionWnd.tbSavePath.Text;
				if (saveOptionWnd.cbIsSaveLeft.Checked && saveOptionWnd.cbIsSaveRight.Checked)
				{
					cmpTree_.Save(
						saveOptionWnd.cbIsSaveCorrInfo.Checked,
						fileName
						);
				}
				else
				{
					if (saveOptionWnd.cbIsSaveLeft.Checked)
					{
						cmpTree_.Save(ltv, fileName);
					}
					else
					{
						cmpTree_.Save(rtv, fileName);
					}
				}
			}
		}

		private void tsbOpen_Click(object sender, EventArgs e)
		{
			LoadOption loadOptionWnd = new LoadOption();
			loadOptionWnd.ShowDialog();
			if (loadOptionWnd.Document == null)
			{
				return;
			}

			if (loadOptionWnd.LeftSource != TreeSide.None)
			{
				cmpTree_.Load(ltv, loadOptionWnd.Document, loadOptionWnd.LeftSource);
			}

			if (loadOptionWnd.RightSource != TreeSide.None)
			{
				cmpTree_.Load(rtv, loadOptionWnd.Document, loadOptionWnd.RightSource);
			}

			if (loadOptionWnd.IsLoadCorr)
			{
				cmpTree_.RebuildCorrespondingInformation();
			}

			//cmpTree_.Refresh();
		}

		private TreeNode currentNode_ = null;

		private void tsbShowInfo_Click(object sender, EventArgs e)
		{
			if (currentNode_ == null)
			{
				return;
			}
			ShowInfo();

		}

		private void tsbComputeChecksum_Click(object sender, EventArgs e)
		{
			Cursor = Cursors.WaitCursor;
			if (currentNode_ == null)
			{
				MessageBox.Show("请先选择节点再执行效验和分析工具。");
				Cursor = Cursors.Arrow;
				return;
			}
			ChecksumOption cmpChecksumWnd = new ChecksumOption();
			cmpChecksumWnd.ShowDialog();

			if (!cmpChecksumWnd.IsOK)
			{
				Cursor = Cursors.Arrow;
				return;
			}

			//收集节点, 
			List<PathNode> initNodeList = (currentNode_.Tag as PathNode).DescendantFiles;
			if (!(currentNode_.Tag as PathNode).IsDirectory)
			{
				initNodeList.Add(currentNode_.Tag as PathNode);
			}


			List<PathNode> filteredNodeList = new List<PathNode>();
			foreach (PathNode pathNode in initNodeList)
			{
				//忽略掉不满足条件的节点
				if (cmpChecksumWnd.ThresholdType == ThresholdType.Least)
				{
					if (pathNode.Size < cmpChecksumWnd.Bound)
					{
						continue;
					}
				}
				if (cmpChecksumWnd.ThresholdType == ThresholdType.Most)
				{
					if (pathNode.Size > cmpChecksumWnd.Bound)
					{
						continue;
					}
				}
				if (
					!cmpChecksumWnd.IsUpdateExistChecksum &&
					!string.IsNullOrEmpty(pathNode.Checksum)
					)
				{
					continue;
				}

				filteredNodeList.Add(pathNode);
			}

			//打开进度对话框
			ChecksumComputeProgress progWnd = new ChecksumComputeProgress(filteredNodeList);
			progWnd.ShowDialog();
			if (progWnd.IsOK)
			{
				MessageBox.Show("已完成效验和计算。");
			}
			else
			{
				MessageBox.Show("效验和计算中断。");
			}
			Cursor = Cursors.Arrow;
		}

		private void tv_NodeMouseDoubleClick(object sender, TreeNodeMouseClickEventArgs e)
		{
			currentNode_ = e.Node;
			ShowInfo();
		}

		private void tsmiShowInfo_Click(object sender, EventArgs e)
		{
			ToolStripMenuItem menuItem = sender as ToolStripMenuItem;
			currentNode_ = menuItem.Owner.Tag as TreeNode;
			ShowInfo();
		}

		private void tsbAddFolder_Click(object sender, EventArgs e)
		{
			if (currentNode_ == null)
			{
				return;
			}

			//打开目录选择对话框
			FolderBrowserDialog fbd = new FolderBrowserDialog();
			fbd.ShowNewFolderButton = false;


			//获取目录并开始添加到目录树当中
			if (fbd.ShowDialog() == DialogResult.OK)
			{
				Cursor oldCursor = Cursor;
				Cursor = Cursors.WaitCursor;
				if (sender == tsbAddFolderShallow)
				{
					cmpTree_.Add(fbd.SelectedPath, currentNode_, false);
				}
				else
				{
					cmpTree_.Add(fbd.SelectedPath, currentNode_, true);
				}
				Cursor = oldCursor;
			}
		}

		private void tsbAddFile_Click(object sender, EventArgs e)
		{
			if (currentNode_ == null)
			{
				return;
			}

			//打开文件选择对话框
			OpenFileDialog ofd = new OpenFileDialog();
			ofd.Multiselect = true;
			if (ofd.ShowDialog() == DialogResult.OK)
			{
				foreach (string filePath in ofd.FileNames)
				{
					cmpTree_.AddAsSub(filePath, currentNode_, false);
				}
			}
		}

		private void tsbExport_Click(object sender, EventArgs e)
		{
			if (currentNode_ == null)
			{
				MessageBox.Show("Please Choose A Node For Export");
				return;
			}

			ExportOption exportOptionWnd = new ExportOption();
			exportOptionWnd.ShowDialog();
			if (!exportOptionWnd.IsOK)
			{
				return;
			}

			//整理需要输出的文件列表
			List<PathNode> fileNodes = null;

			PathNode currentPathNode = currentNode_.Tag as PathNode;
			if (currentPathNode.IsDirectory)
			{
				fileNodes = currentPathNode.DescendantFiles;
			}
			else
			{
				fileNodes = new List<PathNode>();
				fileNodes.Add(currentPathNode);
			}

			List<PathNode> filteredPathNodes = new List<PathNode>();
			foreach (PathNode fileNode in fileNodes)
			{
				if (exportOptionWnd.ExportContent == ExportContent.Common
					&& fileNode.IsEqual)
				{
					filteredPathNodes.Add(fileNode);
				}
				if (exportOptionWnd.ExportContent == ExportContent.New
					&& !fileNode.IsEqual)
				{
					filteredPathNodes.Add(fileNode);
				}
			}

			//根据输出格式输出
			if (exportOptionWnd.ExportFormat == ExportFormat.CopyFile)
			{
				string path = exportOptionWnd.ExportPath;
				string rootPath = null;
				PathNode rootPathNode = currentNode_.Tag as PathNode;
				if (rootPathNode.IsDirectory)
				{
					rootPath = currentNode_.FullPath;
				}
				else
				{
					rootPath = currentNode_.Parent.FullPath;
				}
				CopyFiles copyFileWnd = new CopyFiles(filteredPathNodes, path, rootPath);
				copyFileWnd.ShowDialog();
			}
		}

		private void tsbDelete_Click(object sender, EventArgs e)
		{
			if (currentNode_ == null)
			{
				MessageBox.Show("Please Choose A Node.");
			}

			//根节点没法删除
			if (currentNode_ == currentNode_.TreeView.Nodes[0])
			{
				return;
			}

			currentNode_.Remove();
			(currentNode_.Tag as PathNode).Remove();
		}

		private void tsbDeleteAllSub_Click(object sender, EventArgs e)
		{
			if (currentNode_ == null)
			{
				MessageBox.Show("Please Choose A Node.");
			}

			currentNode_.Nodes.Clear();
			(currentNode_.Tag as PathNode).Clear();
		}
	}

	public abstract class IComputeChecksumCallback
	{
		abstract public bool RaiseCallback(long curPos, long total);
	}

	public class PathNodeCompareParam
	{
		public bool IsCompareName = true;
		public bool IsCompareFileSize = true;
		public bool IsCompareLastWriteTime = true;
		public bool IsCompareChecksum = true;
	}

	public class PathNodeComparer
	{
		public static bool CompareFile(PathNode lnode, PathNode rnode, bool isCmpName, bool isCmpFileSize, bool isCmpLastWriteTime, bool isCmpChecksum)
		{
			if (lnode.IsDirectory || rnode.IsDirectory)
			{
				throw new Exception("应当比较两个文件");
			}

			if (isCmpChecksum)
			{
				if (!string.IsNullOrEmpty(lnode.Checksum) && !string.IsNullOrEmpty(rnode.Checksum))
				{
					return (lnode.Checksum == rnode.Checksum);
				}
			}

			if (isCmpFileSize)
			{
				if (lnode.Size != rnode.Size)
				{
					return false;
				}
			}

			if (isCmpLastWriteTime)
			{
				if (lnode.LastWriteTime != rnode.LastWriteTime)
				{
					return false;
				}
			}

			if (isCmpName)
			{
				if (lnode.Name != rnode.Name)
				{
					return false;
				}
			}

			return true;
		}

		public static bool CompareFile(PathNode lnode, PathNode rnode, PathNodeCompareParam cmpParam)
		{
			return CompareFile(lnode, rnode, cmpParam.IsCompareName, cmpParam.IsCompareFileSize, cmpParam.IsCompareLastWriteTime, cmpParam.IsCompareChecksum);

		}
	}

	public class PathNode
	{
		//从实际目录中加入节点时，使用该方法。
		//它会依据路径查找到相应的文件并获取文件信息。
		public PathNode(string path, PathNode parent, TreeNode treeNode)
		{
			//根节点的情况
			if (parent == null)
			{
				name_ = path;
				parent_ = null;
				treeNode_ = treeNode;
				isDir_ = true;
				return;
			}

			//非根节点必须对应到实际的文件夹上
			if (Directory.Exists(path))
			{
				isDir_ = true;
				name_ = (new DirectoryInfo(path).FullName);
			}
			else if (File.Exists(path))
			{
				isDir_ = false;
				FileInfo fInfo = new FileInfo(path);
				name_ = fInfo.FullName;
				size_ = fInfo.Length;
				lastWriteTime_ = fInfo.LastWriteTime;
			}
			else
			{
				throw new Exception("文件或目录不存在!");
			}
			if (parent != null)
			{
				parent.AppendChild(this);
			}
			treeNode_ = treeNode;
		}

		//该方法为从文件中读取path node信息时使用，不再对目录进行验证和计算。
		public PathNode(
			string path,
			PathNode parent,
			TreeNode treeNode,
			bool isDirectory,
			long fileSize,
			string checksum,
			DateTime lastWriteTime)
		{
			name_ = path;
			isDir_ = isDirectory;
			size_ = fileSize;
			checksum_ = checksum;
			lastWriteTime_ = lastWriteTime;
			treeNode_ = treeNode;

			if (parent != null)
			{
				parent.AppendChild(this);

			}
		}

		public TreeNode TreeNode
		{
			get { return treeNode_; }
		}

		public PathNode Parent
		{
			get { return parent_; }
		}

		public List<PathNode> Files
		{
			get { return new List<PathNode>(childFiles_.Values); }
		}

		public List<PathNode> Directories
		{
			get { return new List<PathNode>(childDirs_.Values); }
		}

		public List<PathNode> DescendantFiles
		{
			get
			{
				List<PathNode> retList = Files;
				foreach (PathNode childPathNode in Directories)
				{
					retList.AddRange(childPathNode.DescendantFiles);
				}
				return retList;
			}
		}

		public PathNode GetFileNode(string fileName)
		{
			PathNode retNode = null;
			return childFiles_.TryGetValue(fileName, out retNode) ? retNode : null;
		}

		public PathNode GetDirectoryNode(string dirName)
		{
			PathNode retNode = null;
			return childDirs_.TryGetValue(dirName, out retNode) ? retNode : null;
		}

		public PathNode CorrespondingNode
		{
			get { return correspondingNode_; }
			set { correspondingNode_ = value; }
		}

		public bool IsCustomCorresponding
		{
			get { return isCustomCorresponding_; }
			set { isCustomCorresponding_ = value; }
		}

		public bool HasCustomCorresponding
		{
			get { return CorrespondingNode != null && isCustomCorresponding_; }
		}

		public bool IsEqual
		{
			get { return isEqual_; }
		}

		public void UpdateCorresponding(PathNode parentNode, PathNodeCompareParam cmpParam)
		{
			if (parentNode.CorrespondingNode != null && parentNode.IsCustomCorresponding)
			{
				return;
			}

			isEqual_ = false;

			//目录仅比较名称
			if (this.IsDirectory)
			{
				CorrespondingNode = parentNode.GetDirectoryNode(this.Name);
				if (CorrespondingNode == null || CorrespondingNode.HasCustomCorresponding)
				{
					CorrespondingNode = null;
					isCustomCorresponding_ = false;
				}
				else
				{
					CorrespondingNode.correspondingNode_ = this;
					CorrespondingNode.isCustomCorresponding_ = false;
				}
				return;
			}

			//文件需要强制比较
			foreach (PathNode node in parentNode.Files)
			{
				if (PathNodeComparer.CompareFile(this, node, cmpParam))
				{
					this.correspondingNode_ = node;
					this.isEqual_ = true;
					node.correspondingNode_ = this;
					node.isEqual_ = true;
					break;
				}
			}
		}

		public void UpdateCorrespondingRecursive(PathNode rootNode, PathNodeCompareParam cmpParam)
		{
			if (!this.IsDirectory)
			{
				throw new Exception("无法对文件节点递归更新!");
			}

			isEqual_ = true;

			foreach (PathNode fileNode in childFiles_.Values)
			{
				fileNode.UpdateCorresponding(rootNode, cmpParam);
				isEqual_ = isEqual_ && fileNode.isEqual_;
			}

			foreach (PathNode dirNode in childDirs_.Values)
			{
				dirNode.UpdateCorresponding(rootNode, cmpParam);
				PathNode node = dirNode.correspondingNode_;
				if (node == null)
				{
					isEqual_ = false;
				}
				else
				{
					dirNode.UpdateCorrespondingRecursive(node, cmpParam);
					isEqual_ = isEqual_ && dirNode.isEqual_;
				}
			}

			if (isEqual_ == true)
			{
				isEqual_ =
					(childDirs_.Count == rootNode.childDirs_.Count) && (childFiles_.Count == rootNode.childFiles_.Count);
			}

			rootNode.isEqual_ = isEqual_;
		}

		public void AppendChild(PathNode node)
		{
			node.parent_ = this;
			if (node.IsDirectory)
			{
				childDirs_.Add(node.Name, node);
			}
			else
			{
				childFiles_.Add(node.Name, node);
			}
		}

		public void Clear()
		{
			childDirs_.Clear();
			childFiles_.Clear();
		}

		public void RemoveChild(PathNode node)
		{
			RemoveCorrespondingRecursive(node);
			if (node.isDir_)
			{
				childDirs_.Remove(node.Name);
			}
			else
			{
				childFiles_.Remove(node.Name);
			}
		}

		public void Remove()
		{
			if (parent_ == null)
			{
				return;
			}

			parent_.RemoveChild(this);
			this.parent_ = null;
		}

		public void RemoveCorresponding()
		{
			if (CorrespondingNode != null)
			{
				CorrespondingNode.correspondingNode_ = null;
				CorrespondingNode.isCustomCorresponding_ = false;
				CorrespondingNode.isEqual_ = false;

				correspondingNode_ = null;
				isCustomCorresponding_ = false;
				isEqual_ = false;
			}
		}

		public void RemoveCorrespondingRecursive(PathNode node)
		{
			node.RemoveCorresponding();

			foreach (PathNode fileNode in node.childFiles_.Values)
			{
				RemoveCorrespondingRecursive(fileNode);
			}

			foreach (PathNode dirNode in node.childDirs_.Values)
			{
				RemoveCorrespondingRecursive(dirNode);
			}
		}

		public string ComputeChecksum()
		{
			if (isDir_)
			{
				checksum_ = "";
			}
			else
			{
				FileStream fstr = null;
				try
				{
					fstr = new FileStream(name_, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
					MD5CryptoServiceProvider md5er = new MD5CryptoServiceProvider();
					md5er.ComputeHash(fstr);
					StringBuilder md5str = new StringBuilder();
					foreach (byte b in md5er.Hash)
					{
						md5str.AppendFormat("{0:X2}", b);
					}
					checksum_ = md5str.ToString();
				}
				catch (Exception ex)
				{
					return ex.Message;
				}
				finally
				{
					if (fstr != null)
					{
						fstr.Close();
					}
				}
			}

			return null;
		}

		public string ComputeChecksumAsync(IComputeChecksumCallback callback)
		{
			if (isDir_)
			{
				checksum_ = "";
			}
			else
			{
				FileStream fstr = null;
				try
				{
					fstr = new FileStream(name_, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
					MD5CryptoServiceProvider md5er = new MD5CryptoServiceProvider();
					int bufsize = 64 * 1024; //64K Buffer
					byte[] buf = new byte[bufsize];
					long curpos = 0;
					while (true)
					{
						int readCount = fstr.Read(buf, 0, bufsize);
						if (readCount < bufsize)
						{
							md5er.TransformFinalBlock(buf, 0, readCount);
							curpos = size_;
							break;
						}
						else
						{
							md5er.TransformBlock(buf, 0, readCount, buf, 0);
							curpos += readCount;
						}
						if (callback != null)
						{
							if (!callback.RaiseCallback(curpos, size_))
							{
								throw new Exception("Checksum computation will be aborted by user.");
							}
						}
					}

					StringBuilder md5str = new StringBuilder();
					foreach (byte b in md5er.Hash)
					{
						md5str.AppendFormat("{0:X2}", b);
					}
					checksum_ = md5str.ToString();
				}
				catch (Exception ex)
				{
					return ex.Message;
				}
				finally
				{
					if (fstr != null)
					{
						fstr.Close();
					}
				}
			}

			return null;
		}
		public bool IsDirectory
		{
			get { return isDir_; }
		}

		public string BaseName
		{
			get { return Path.GetFileNameWithoutExtension(name_); }
		}

		public string Extension
		{
			get { return Path.GetExtension(name_); }
		}

		public string Name
		{
			get { return Path.GetFileName(name_); }
		}

		public string FullName
		{
			get { return name_; }
		}

		public long Size
		{
			get { return size_; }
		}

		public DateTime LastWriteTime
		{
			get { return lastWriteTime_; }
		}

		public string Checksum
		{
			get { return checksum_; }
		}

		private bool isDir_;
		private string name_;
		private long size_;
		private DateTime lastWriteTime_;
		private string checksum_;

		private PathNode parent_;
		private TreeNode treeNode_;
		private Dictionary<string, PathNode> childFiles_ = new Dictionary<string, PathNode>();
		private Dictionary<string, PathNode> childDirs_ = new Dictionary<string, PathNode>();
		private PathNode correspondingNode_ = null;
		private bool isCustomCorresponding_ = false;

		private bool isEqual_ = false;
	}

	public enum TreeSide
	{
		None,
		Left,
		Right
	}

	public class ComparisonTree
	{
		private TreeView ltv_;
		private TreeView rtv_;

		private ContextMenuStrip ctxtMenu_;

		public ComparisonTree(TreeView ltv, TreeView rtv, ContextMenuStrip menu)
		{
			ltv_ = ltv;
			rtv_ = rtv;
			ctxtMenu_ = menu;

			TreeNode lroot = new TreeNode("Root");
			TreeNode rroot = new TreeNode("Root");

			lroot.ImageIndex = 1;
			lroot.SelectedImageIndex = 1;

			rroot.ImageIndex = 1;
			rroot.SelectedImageIndex = 1;

			PathNode lrootPathNode = new PathNode("Root", null, lroot);
			PathNode rrootPathNode = new PathNode("Root", null, rroot);
			lrootPathNode.CorrespondingNode = rrootPathNode;
			rrootPathNode.CorrespondingNode = lrootPathNode;
			lroot.Tag = lrootPathNode;
			rroot.Tag = rrootPathNode;

			ltv_.Nodes.Add(lroot);
			rtv_.Nodes.Add(rroot);
		}

		public void AddAsSub(string path, TreeNode parentNode, bool isIncludeSub)
		{
			TreeNode childNode = new TreeNode();
			PathNode pathInfo = new PathNode(path, parentNode.Tag as PathNode, childNode);
			childNode.Tag = pathInfo;
			childNode.Text = pathInfo.Name;
			if (pathInfo.IsDirectory)
			{
				childNode.ImageIndex = 1;
				childNode.SelectedImageIndex = 1;
			}
			else
			{
				childNode.ImageIndex = 0;
				childNode.SelectedImageIndex = 0;
			}

			parentNode.Nodes.Add(childNode);

			if (isIncludeSub && pathInfo.IsDirectory)
			{
				Add(path, childNode, isIncludeSub);
			}
		}

		public void Add(string path, TreeNode parentNode, bool isIncludeSub)
		{
			//MessageBox.Show("Add " + (isIncludeSub ? "Recursive" : "Shallow"));
			string childNames = "";
			DirectoryInfo dirInfo = new DirectoryInfo(path);
			foreach (FileSystemInfo childDirInfo in dirInfo.GetFileSystemInfos())
			{
				TreeNode childNode = new TreeNode();
				PathNode pathInfo = new PathNode(childDirInfo.FullName, parentNode.Tag as PathNode, childNode);
				childNode.Tag = pathInfo;
				childNode.Text = pathInfo.Name;
				if (pathInfo.IsDirectory)
				{
					childNode.ImageIndex = 1;
					childNode.SelectedImageIndex = 1;
				}
				else
				{
					childNode.ImageIndex = 0;
					childNode.SelectedImageIndex = 0;
				}

				parentNode.Nodes.Add(childNode);
				childNames += childNode.Text + ";";
				if (isIncludeSub && pathInfo.IsDirectory)
				{
					Add(pathInfo.FullName, childNode, true);
				}
			}
		}

		public void AddCorresponding(TreeNode lhs, TreeNode rhs)
		{
		}

		public void Refresh()
		{
			ltv_.BeginUpdate();
			rtv_.BeginUpdate();
			RefreshRecursive(ltv_.Nodes[0]);
			RefreshRecursive(rtv_.Nodes[0]);
			ltv_.EndUpdate();
			rtv_.EndUpdate();
		}

		public void RefreshRecursive(TreeNode node)
		{
			PathNode pnode = node.Tag as PathNode;
			node.ForeColor = Color.FromArgb(160, 0, 0);
			if (pnode.CorrespondingNode != null)
			{
				node.ForeColor = Color.DarkOrange;
			}
			if (pnode.IsEqual)
			{
				node.ForeColor = Color.DarkBlue;
			}

			foreach (TreeNode childNode in node.Nodes)
			{
				RefreshRecursive(childNode);
			}
		}

		public void Compare()
		{
			(ltv_.Nodes[0].Tag as PathNode).UpdateCorrespondingRecursive(rtv_.Nodes[0].Tag as PathNode, new PathNodeCompareParam());
		}

		//保存一侧
		public void Save(TreeView tv, string fileName)
		{
			XmlDocument doc = new XmlDocument();
			doc.AppendChild(doc.CreateElement("PathTree"));
			doc.DocumentElement.AppendChild(doc.CreateElement("PathNode"));
			SaveNodeRecursive(tv.Nodes[0], doc.DocumentElement.FirstChild as XmlElement, false);
			doc.Save(fileName);
		}

		public void Save(bool isIncludeCorrespondingInfo, string fileName)
		{
			XmlDocument doc = new XmlDocument();
			doc.AppendChild(doc.CreateElement("PathTreePair"));
			XmlElement leftElem = doc.CreateElement("PathNode");
			XmlElement rightElem = doc.CreateElement("PathNode");
			doc.ChildNodes[0].AppendChild(leftElem);
			doc.ChildNodes[0].AppendChild(rightElem);
			SaveNodeRecursive(ltv_.Nodes[0], leftElem, isIncludeCorrespondingInfo);
			SaveNodeRecursive(rtv_.Nodes[0], rightElem, isIncludeCorrespondingInfo);
			doc.Save(fileName);
		}

		public void SaveNodeRecursive(TreeNode node, XmlElement curElem, bool isSaveCorrInfo)
		{
			PathNode pathNode = node.Tag as PathNode;
			XmlDocument doc = curElem.OwnerDocument;

			//保存单个节点
			curElem.SetAttribute("path", pathNode.FullName);
			curElem.SetAttribute("tree_path", node.FullPath);
			if (pathNode.CorrespondingNode != null && isSaveCorrInfo)
			{
				curElem.SetAttribute("corresponding_node_path",
					pathNode.CorrespondingNode.TreeNode.FullPath);
				curElem.SetAttribute("is_custom_corresponding_node",
					pathNode.CorrespondingNode.IsCustomCorresponding.ToString());
			}
			curElem.SetAttribute("type", pathNode.IsDirectory ? "directory" : "file");

			if (!pathNode.IsDirectory)
			{
				curElem.SetAttribute("last_write_time", pathNode.LastWriteTime.ToString());
				curElem.SetAttribute("file_size", pathNode.Size.ToString());
				curElem.SetAttribute("checksum", pathNode.Checksum);
			}

			//保存子节点
			foreach (TreeNode childNode in node.Nodes)
			{
				XmlElement childElem = doc.CreateElement("PathNode");
				SaveNodeRecursive(childNode, childElem, isSaveCorrInfo);
				curElem.AppendChild(childElem);
			}
		}

		public void Load(TreeView tv, XmlDocument doc, TreeSide fromSide)
		{
			if (doc.DocumentElement.Name == "PathTree")
			{
				if (fromSide == TreeSide.Left)
				{
					XmlElement elem = doc.DocumentElement.SelectNodes("PathNode")[0] as XmlElement;
					LoadNodeRecursive(tv.Nodes[0], elem, false);
				}
				else
				{
					throw new Exception("使用了不存在的信息！");
				}
			}
			else if (doc.DocumentElement.Name == "PathTreePair")
			{
				XmlElement elem = null;
				elem = doc.DocumentElement.SelectNodes("descendant::PathNode")[fromSide == TreeSide.Left ? 0 : 1] as XmlElement;
				LoadNodeRecursive(tv.Nodes[0], elem, false);
			}
		}

		public void LoadNodeRecursive(TreeNode node, XmlElement curElem, bool isLoadCorrInfo)
		{
			//读取当前节点
			PathNode pathNode = node.Tag as PathNode;

			//读取子节点
			foreach (XmlNode childNode in curElem.ChildNodes)
			{
				//如果不是所需要的节点直接忽略
				if (childNode.NodeType != XmlNodeType.Element)
				{
					continue;
				}
				XmlElement childElem = childNode as XmlElement;
				if (childElem.Name != "PathNode")
				{
					continue;
				}

				//否则创建子节点
				string path = childElem.GetAttribute("path");

				string checksum = childElem.HasAttribute("checksum") ? childElem.GetAttribute("checksum") : "";
				bool isDir = (childElem.GetAttribute("type") == "directory");
				DateTime lastWriteTime = childElem.HasAttribute("last_write_time") ? DateTime.Parse(childElem.GetAttribute("last_write_time")) : new DateTime();
				long fileSize = childElem.HasAttribute("file_size") ? long.Parse(childElem.GetAttribute("file_size")) : 0;

				TreeNode childTreeNode = new TreeNode();
				PathNode childPathNode = new PathNode(
					childElem.GetAttribute("path"),
					pathNode,
					childTreeNode,
					isDir,
					fileSize,
					checksum,
					lastWriteTime
					);

				childTreeNode.Tag = childPathNode;
				childTreeNode.Text = childPathNode.Name;
				if (childPathNode.IsDirectory)
				{
					childTreeNode.ImageIndex = 1;
					childTreeNode.SelectedImageIndex = 1;
				}
				else
				{
					childTreeNode.ImageIndex = 0;
					childTreeNode.SelectedImageIndex = 0;
				}
				node.Nodes.Add(childTreeNode);

				LoadNodeRecursive(childTreeNode, childElem, isLoadCorrInfo);
			}
		}

		//重建节点的对应信息
		public void RebuildCorrespondingInformation()
		{
			//现有的版本不使用保存的节点对应关系，而是重新创建
			Compare();
			Refresh();
		}
	}

}