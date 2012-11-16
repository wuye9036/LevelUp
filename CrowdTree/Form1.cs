using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace CrowdTree
{
	public partial class Form1 : Form
	{
		private LayoutTreeNode rootNode;
		public Form1()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			LayoutTree lTree = new LayoutTree();
			lTree.VerticalSpacer = 20.0f;
			lTree.HorizontalSpacer = 30.0f;
			TextLayoutTreeNode root = lTree.CreateNode<TextLayoutTreeNode>(null);
			root.Text = "root";
			TextLayoutTreeNode c0 = lTree.CreateNode<TextLayoutTreeNode>(root);
			c0.Text = "c0";
			TextLayoutTreeNode c1 = lTree.CreateNode<TextLayoutTreeNode>(root);
			c1.Text = "aaaaaaaaaaaaa\naaaaaaaaaaaaa";
			TextLayoutTreeNode c2 = lTree.CreateNode<TextLayoutTreeNode>(c1);
			c2.Text = "c2";
			TextLayoutTreeNode c3 = lTree.CreateNode<TextLayoutTreeNode>(c1);
			c3.Text = "bbbbbbbbbbbb";

			rootNode = root;
		}

		private void DrawTree()
		{
			Graphics g = this.CreateGraphics();
			g.Clear(this.BackColor);
			rootNode.Owner.ResetLayout();

			rootNode.CalculateSizeRecursive(80, new Font("Î¢ÈíÑÅºÚ", 14), g);
			rootNode.Layout();
			DrawTreeNodeRecursive(g, rootNode);
		}

		private void DrawTreeNodeRecursive(Graphics g, LayoutTreeNode node)
		{
			g.DrawRectangle(Pens.Black, Rectangle.Round(node.Extent));
			node.Draw(g);
			foreach (LayoutTreeNode childNode in node.Children)
			{
				DrawTreeNodeRecursive(g, childNode);
			}
		}

		private void Form1_Paint(object sender, PaintEventArgs e)
		{
			DrawTree();
		}
	}
}