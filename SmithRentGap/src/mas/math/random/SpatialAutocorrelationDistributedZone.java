package mas.math.random;

import java.util.*;

import mas.math.vector.Grid2DPosition;
import mas.math.vector.Vector;

public class SpatialAutocorrelationDistributedZone extends DistributedZone {
	public SpatialAutocorrelationDistributedZone( Randomizer rand, int width, int height ){
		super( rand, width, height );
		
		// initialize randomizer
		randomPosXGenerator = new UniformRandomizer(0.0, width);
		randomPosYGenerator = new UniformRandomizer(0.0, height);
		
		// fill with randomize
		data = new ArrayList<Float>( width * height );
		for ( int i = 0; i < width * height; ++i ){
			data.add( rand.nextFloat() );
		}
		
		// Enhance spatial autocorrelation distributed zone
		agglomerate();
	}

	@Override
	public float getValue(int x, int y) {
		return data.get(y * height + x);
	}
	
	private float getValue(Grid2DPosition pos){
		return getValue(pos.x, pos.y);
	}
	
	private void setValue(int x, int y, float v ){
		data.set(y * height + x, v);
	}
	
	private void setValue( Grid2DPosition pos, float v ){
		setValue(pos.x, pos.y, v);
	}
	
	private Grid2DPosition generateRandomPosition(){
		int x = randomPosXGenerator.nextInt(); 
		int y = randomPosYGenerator.nextInt();
		return new Grid2DPosition(x, y);
	}
	
	public boolean isNeedExchange(
			Grid2DPosition sourcePt, float sourceValue,
			Grid2DPosition destPt0, float destValue0,
			Grid2DPosition destPt1, float destValue1
			){
		float diff0 = Math.abs(sourceValue - destValue0);
		float distSqr0 = Vector.DistanceSq(sourcePt, destPt0);
		float diff1 = Math.abs(sourceValue - destValue1);
		float distSqr1 = Vector.DistanceSq(sourcePt, destPt1);
		
		return (distSqr1 - distSqr0) * (diff1 - diff0) < 0.0f;
	}
	
	private void agglomerate(){
		// first, choose a random point
		Grid2DPosition centerPos = generateRandomPosition();
		float centerValue = getValue(centerPos);
		
		// pick up some point pairs( 1/4 of cells count ), and for each pair,
		for ( int iPair = 0; iPair < width * height / 4; ++ iPair ){
			Grid2DPosition pos0 = generateRandomPosition();
			Grid2DPosition pos1 = generateRandomPosition();
			
			float value0 = getValue(pos0);
			float value1 = getValue(pos1);
		
			// calculate the correlation coefficient of two points.
			// if the near one has lower correlation coefficient, swap two points
			if( isNeedExchange(centerPos, centerValue, pos0, value0, pos1, value1) ){
				setValue(pos0, value1);
				setValue(pos1, value0);
			}
		}
	}
	
	private ArrayList<Float> data;
	private Randomizer randomPosXGenerator;
	private Randomizer randomPosYGenerator;
	@Override
	public float getAverage() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public float getMax() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public float getMin() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public float getStandardDev() {
		// TODO Auto-generated method stub
		return 0;
	}
}
