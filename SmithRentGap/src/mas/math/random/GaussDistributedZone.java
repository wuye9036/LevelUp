package mas.math.random;

public class GaussDistributedZone extends DistributedZone {
	public GaussDistributedZone(int width, int height, double mean, double delta, int kernelSize, double T) {
		super(new NormalRandomizer(0.0, 1.0), width, height);
		
		// initialize constant
		this.sqrtPi = Math.sqrt(Math.PI);
		
		// initialize parameters
		this.width = width;
		this.height = height;
		this.kernelSize = kernelSize;
		this.delta = delta;
		this.T = T;
		this.mean = mean;
		
		initializeData();
		initializeFilterKernel();
		convolve();
		updateStatistics();
	}

	public void regenerate(){
		initializeData();
		convolve();
		updateStatistics();
	}
	
	@Override
	public float getValue(int x, int y) {
		return (float)(convolvedData[y][x] + mean);
	}
	
	private void initializeData(){
		if (data == null){
			data = new double[height][width];
		}
		for ( int i = 0; i < height; ++i ){
			for ( int j = 0; j < width; ++j){
				data[i][j] = rand.nextDouble();
			}
		}
	}
	
	private void initializeFilterKernel(){
		kernel = new double[kernelSize][kernelSize];
		kernelSummaryTable = new double[kernelSize][kernelSize];
		
		// calculate kernel
		int kernelRadius = (kernelSize - 1) / 2;
		for( int i = 0; i <= kernelRadius; ++i){
			for( int j = 0; j < kernelRadius; ++j){
				double w = weight(i, j);
				kernel[kernelRadius - i][kernelRadius - j] = w;
				kernel[kernelRadius - i][kernelRadius + j] = w;
				kernel[kernelRadius + i][kernelRadius - j] = w;
				kernel[kernelRadius + i][kernelRadius + j] = w;
			}
		}
		
		// calculate kernel summary table
		kernelSummaryTable[0][0] = kernel[0][0];
		for ( int i = 0; i < kernelSize; ++i){
			for( int j = 0; j < kernelSize; ++j){
				kernelSummaryTable[i][j] = kernelSum(i, j-1) + kernelSum(i-1, j) - kernelSum(i-1, j-1) + kernel[i][j];
			}
		}
	}
	private void convolve(){
		if (convolvedData == null){
			convolvedData = new double[height][width];
		}
		
		for (int y = 0; y < height; ++y) {
			for (int x = 0; x < width; ++x) {
				convolvedData[y][x] = convolveCell(x, y);
			}
		}
	}
	
	private double convolveCell(int x, int y){
		int kernelRadius = (kernelSize - 1) / 2;

		int dataLeft = Math.max(x - kernelRadius, 0);
		int dataRight = Math.min(x + kernelRadius , width-1);
		int dataTop = Math.max(y - kernelRadius, 0);
		int dataBottom = Math.min(y + kernelRadius, height-1);

		int kernelLeft = kernelRadius - ( x - dataLeft );
		int kernelRight = kernelRadius + ( dataRight - x );
		int kernelTop = kernelRadius - ( y - dataTop );
		int kernelBottom = kernelRadius + ( dataBottom - y );

		double sum = 0.0;
		for (int y_convolve = dataTop; y_convolve <= dataBottom; ++y_convolve) {
			for (int x_convolve = dataLeft; x_convolve <= dataRight; ++x_convolve) {
				sum +=
					data[y_convolve][x_convolve] * kernel[y_convolve - dataTop + kernelTop][x_convolve - dataLeft + kernelLeft];
			}
		}
		return sum / kernelSum(kernelLeft, kernelRight, kernelTop, kernelBottom) * kernelSum(0, kernelSize-1, 0, kernelSize-1);
	}
	
	private double weight(int i, int j){
		if (i == 0 && j == 0){
			// 当是像素中心时，取1/4边长处的值作为距离值。
			return ( 2.0 * delta ) / ( sqrtPi * T )  * Math.exp( - 2.0 * ( 1.0 / 16.0 ) / (T * T) ); 
		}
		return ( 2.0 * delta ) / ( sqrtPi * T )  * Math.exp( - 2.0 * ( i * i + j * j ) / (T * T) ); 
	}
	private double kernelSum(int b, int r){
		if( r < 0 || b < 0){
			return 0.0;
		}
		return kernelSummaryTable[b][r];
	}
	private double kernelSum(int l, int r, int t, int b){
		return kernelSum(b, r) - kernelSum(t-1, r) - kernelSum(b, l-1) + kernelSum(t-1, l-1);
	}
	
	private void updateStatistics(){
		actualMax = Float.NEGATIVE_INFINITY;
		actualMin = Float.POSITIVE_INFINITY;
		double total = 0.0f;
		actualAverage = 0.0f;
		actualStddev = 0.0f;
		
		for (int i = 0; i < height; ++i){
			for (int j = 0; j < width; ++j){
				double v = convolvedData[i][j];
				total += v;
				actualMax = Math.max(v, actualMax);
				actualMin = Math.min(v, actualMin);
			}
		}
		
		actualAverage = total / (width * height);
		
		for (int i = 0; i < height; ++i){
			for (int j = 0; j < width; ++j){
				double v = convolvedData[i][j];
				actualStddev += (v - actualAverage) * (v - actualAverage);
			}
		}
		actualStddev = Math.sqrt(actualStddev / (width * height));
		
		actualAverage += mean;
		actualMin += mean;
		actualMax += mean;
	}
	
	private double data[][];
	private double convolvedData[][];
	
	private double actualMax;
	private double actualMin;
	private double actualAverage;
	private double actualStddev;
	
	private int width;
	private int height;
	
	private double T;
	private double delta;
	private double mean;
	private double sqrtPi;
	
	private double kernel[][];
	private double kernelSummaryTable[][];
	private int kernelSize;
	@Override
	public float getAverage() {
		return (float) actualAverage;
	}

	@Override
	public float getMax() {
		return (float)actualMax;
	}

	@Override
	public float getMin() {
		return (float)actualMin;
	}

	@Override
	public float getStandardDev() {
		return (float)actualStddev;
	}
}
