using System;
using System.Collections.Generic;
using System.Text;

namespace SwarmExperimentalAnalyser.UI.Sandbox {
	abstract class SurfaceGenerator {
		#region "Events"
		public delegate void OnTrackEventHandler (double[,] temporalData, ref bool isContinue);
		public OnTrackEventHandler OnTrack = null; 
		#endregion

		abstract public double[,] Generate(int size);
		protected bool NotifyOnTrack(double[,] temporalData) {
			bool isContinue = true;
			if (OnTrack != null) {
				OnTrack(temporalData, ref isContinue);
			}
			return isContinue;
		}
	}
}
