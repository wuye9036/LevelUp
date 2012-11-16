using System;
using System.Collections.Generic;
using System.Text;
using MathNet.Numerics;
using MathNet.Numerics.Distributions;

namespace SwarmExperimentalAnalyser.UI.Sandbox {
	class GaussSurfaceGenerator: SurfaceGenerator {
		public GaussSurfaceGenerator() {
		}
		
		// kernel size 指全窗口大小
		public double[,] Generate(int size, double mean, double delta, int kernelSize, double T) {
			this.mean = mean;
			this.delta = delta;

			double[,] data = InitializeDataArray(size);
			InitializeFilterKernel(kernelSize, delta, T);
			return Convolve(size, data, kernelSize);
		}

		public override double[,] Generate(int size) {
			return Generate(size, mean, delta, DefaultFilterWindowSize, (double)size / 4 );	
		}

		private double[,] InitializeDataArray(int size) {
			double[,] data = new double[size, size];
			NormalDistribution normalDist = new NormalDistribution(mean, delta);
			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					data[i, j] = normalDist.NextDouble();
				}
			}
			return data;
		}

		private double[,] Convolve(int size, double[,] data, int kernelSize) {
			double[,] convolvedData = new double[size, size];
			for (int i = 0; i < size; ++i) {
				for (int j = 0; j < size; ++j) {
					convolvedData[i, j] = ConvolveCell(i, j, size, kernelSize, data);
				}
			}
			return convolvedData;
		}
		private double ConvolveCell(int i, int j, int size, int kernelSize, double[,] data) {
			int kernelRadius = (kernelSize - 1) / 2;

			int dataLeft = Math.Max(i - kernelRadius, 0);
			int dataRight = Math.Min(i + kernelRadius , size-1);
			int dataTop = Math.Max(j - kernelRadius, 0);
			int dataBottom = Math.Min(j + kernelRadius, size-1);

			int kernelLeft = kernelRadius - ( i - dataLeft );
			int kernelRight = kernelRadius + ( dataRight - i );
			int kernelTop = kernelRadius - ( j - dataTop );
			int kernelBottom = kernelRadius + ( dataBottom - j );

			double sum = 0.0;
			for (int i_convolve = dataLeft; i_convolve <= dataRight; ++i_convolve) {
				for (int j_convolve = dataTop; j_convolve <= dataBottom; ++j_convolve) {
					sum +=
						data[i_convolve, j_convolve] * weightTable[i_convolve - dataLeft + kernelLeft, j_convolve - dataTop + kernelTop];
				}
			}
			return sum / WeightSummary(kernelLeft, kernelRight, kernelTop, kernelBottom);
		}

		private void InitializeFilterKernel(int kernelSize, double delta, double T) {
			weightTable = new double[kernelSize, kernelSize];
			weightSummaryTable = new double[kernelSize, kernelSize];

			// Initialize Kernel
			int kernelRadius = (kernelSize - 1) / 2;
			weightTable[kernelRadius, kernelRadius] = Weight(0, 0, delta, T);
			for (int i = 0; i <= kernelRadius; ++i){
				for( int j = 0; j <= kernelRadius; ++j){
					double w = Weight(i, j, delta, T);

					weightTable[kernelRadius - i, kernelRadius - j] = w;
					weightTable[kernelRadius - i, kernelRadius + j] = w;
					weightTable[kernelRadius + i, kernelRadius - j] = w;
					weightTable[kernelRadius + i, kernelRadius + j] = w;
				}
			}

			// Initialize Weight Summary Table
			weightSummaryTable[0, 0] = weightTable[0, 0];
			for(int i = 0; i < kernelSize; ++ i){
				for ( int j = 0; j < kernelSize; ++j){
					weightSummaryTable[i, j] = WeightSummary(i, j-1) + WeightSummary(i-1, j) - WeightSummary(i-1, j-1) + weightTable[i, j];
				}
			}
		}

		private double Weight(int i, int j, double delta, double T){
			return (2.0 * delta) / (SqrtPi * T) * Math.Exp( - 2.0 * ( i * i + j * j ) / (T * T) );
		}

		private double WeightSummary(int r, int b){
			if ( r < 0 || b < 0 ){
				return 0.0;
			}
			return weightSummaryTable[r, b];
		}
		private double WeightSummary( int l, int r, int t, int b){
			return WeightSummary(r, b) - WeightSummary(r, t-1) - WeightSummary(l-1, b) + WeightSummary(l-1, t-1);
		}

		private double[,] weightSummaryTable;
		private double[,] weightTable;

		private double mean;
		private double delta;

		public const double SqrtPi = 1.7724538509055160272981674833411;
		public const int DefaultFilterWindowSize = 5;
	}
}
