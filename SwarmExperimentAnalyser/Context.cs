using System;
using System.Collections.Generic;
using System.Text;
using SwarmExperimentalAnalyser.Model.Experiment;
using System.Data;
using SwarmExperimentalAnalyser.UI.ExperimentInformation;

namespace SwarmExperimentalAnalyser {
	public struct DataItem {
		public DataItem(object isTimeSeries, object index) {
			IsTimeSeries = (bool)isTimeSeries;
			Index = (int)index;
		}

		public bool Equals(DataItem obj) {
			return IsTimeSeries == obj.IsTimeSeries && Index == obj.Index;
		}
		public bool IsTimeSeries;
		public int Index;
	}

	public class Context {

		#region "Events"
		public delegate void OnContextStateChanged(Context ctxt);

		public OnContextStateChanged FocusedExperimentChanged;
		public OnContextStateChanged SelectedExperimentChanged;
		public OnContextStateChanged FocusedItemChanged;
		public OnContextStateChanged BatchExperimentChanged;
		public OnContextStateChanged ExperimentTableChanged;

		private void NullableInvoke(OnContextStateChanged eventHandler) {
			if (eventHandler == null) {
				return;
			}
			eventHandler(this);
		}
		#endregion

		public Context() {
		}

		public BatchExperiment BatchExperiment {
			get { return batch; }
			set {
				if (batch == value) {
					return;
				}
				batch = value;
				NullableInvoke(BatchExperimentChanged);
			}
		}

		public Experiment FocusedExperiment {
			get { return focusedExp; }
			set {
				if (focusedExp == value) {
					return;
				}
				focusedExp = value;
				NullableInvoke(FocusedExperimentChanged);
			}
		}

		public ExperimentTable ExperimentTable {
			get { return experimentTable; }
			set {
				if (experimentTable == value) {
					return;
				}
				experimentTable = value;
				NullableInvoke(ExperimentTableChanged);
			}
		}

		public DataItem FocusedItem {
			get { return focusedItem; }
			set {
				if (focusedItem.Equals( value) ) {
					return;
				}
				focusedItem = value;
				NullableInvoke(FocusedItemChanged);
			}
		}

		public List<int> SelectedExperiments {
			get { return new List<int>(selectedExp.Keys); }
			set {
				selectedExp = new Dictionary<int, object>();
				foreach (int selectedExpIdx in value) {
					selectedExp[selectedExpIdx] = null;
				}
				NullableInvoke(SelectedExperimentChanged);
			}
		}

		public void SetExperimentSelected(bool selected, params int[] expIds) {
			if (selected) {
				foreach (int selectedExpIdx in expIds) {
					selectedExp[selectedExpIdx] = null;
				}
			} else {
				foreach (int selectedExpIdx in expIds) {
					selectedExp.Remove(selectedExpIdx);
				}
			}
			NullableInvoke(SelectedExperimentChanged);
		}

		public void ToggleExperimentSelected(params int[] expIds) {
			foreach (int selectedExpIdx in expIds) {
				if (!selectedExp.Remove(selectedExpIdx)) {
					selectedExp.Add(selectedExpIdx, null);
				}
			}
			NullableInvoke(SelectedExperimentChanged);
		}

		private Experiment focusedExp = null;
		private Dictionary<int, object> selectedExp;
		private DataItem focusedItem;
		private BatchExperiment batch;
		private ExperimentTable experimentTable;
	}
}
