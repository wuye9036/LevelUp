import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import mas.math.vector.Grid2DPosition;
import mas.math.vector.Vector;
import swarm.defobj.Zone;
import swarm.space.Grid2dImpl;

public class ResearchArea extends Grid2dImpl {
	static public float lambda = 0.02f;
	static public double decayConstant = Math.exp(-lambda);
	static public float maxDisplayRent = 127;
	public int width;
	public int height;
	
	private ArrayList<PropertyUnit> pus;
	private ArrayList<Float> temporaryCapitalRent;
	private RentGapModelSwarm model;
	private float acr;
	
	public ResearchArea(Zone zone, int w, int h, RentGapModelSwarm model ){
		super(zone, w, h);
		
		this.model = model;
		width = w;
		height = h;
		
		//
		lambda = 0.02f;
		
		pus = new ArrayList<PropertyUnit>();
		temporaryCapitalRent = new ArrayList<Float>(width*height);
		for(int i_x = 0; i_x < width; ++i_x){
			for(int i_y = 0; i_y < height; ++i_y){
				PropertyUnit pu = new PropertyUnit();
				pu.potentialRent = model.potentialRentGen.getValue(i_x, i_y);
				pu.orgCaptialRent = pu.potentialRent;
				pu.time = Util.randomInt(0, 10);
				pu.exp_inv_lambda_x_time = Math.exp(-lambda*pu.time);
				pu.capitalRent = (float) (pu.orgCaptialRent * (1.0f / Math.exp(lambda*pu.time)));
				
				pus.add(pu);
			}
		}
	}
	
	private static int fast_floor_i(float v){
		return v<0? ( v == (int)v ? (int)v : (int)v-1 ) :(int)v;
	}
	
	private int calcStartPos(int x, float radius){
		return (int)((float)x - radius);
	}
	private int calcEndPos(int x, float radius){
		return -fast_floor_i(-(float)x - radius);
	}
	
	private boolean farThan(Grid2DPosition pos0, Grid2DPosition pos1, float dist){
		return Vector.DistanceSq(pos0, pos1) > dist * dist;
	}
	
//	private int normalizeRent(float rent){
//		float normalizedRent = rent / model.potentialRentGen.normalize(rent) * maxDisplayRent;
//		return (int)normalizedRent;
//	}

	private void decayPUs(){
		Grid2DPosition pos = new Grid2DPosition(0, 0);
		for(int i_x = 0; i_x < width; ++i_x){
			for(int i_y = 0; i_y < height; ++i_y){
				pos.x = i_x;
				pos.y = i_y;
				PropertyUnit pu = getPropertyUnit(pos);
				pu.time += 1;
				pu.exp_inv_lambda_x_time *= decayConstant;
				pu.capitalRent = (float) (pu.orgCaptialRent * pu.exp_inv_lambda_x_time);
			}
		}
	}
	private void rehabilitatePUs(){
		Grid2DPosition pos = new Grid2DPosition(0, 0);
		temporaryCapitalRent.clear();
		for(int i_y = 0; i_y < height; ++i_y){
			for(int i_x = 0; i_x < width; ++i_x){
				pos.x = i_x;
				pos.y = i_y;
				PropertyUnit pu = getPropertyUnit(pos);
				
				float nr = getNeighbourRent(pos);
				float cr = pu.capitalRent;
				float constructionCost = getConstructionCost(pu);
				if ( nr - cr > constructionCost){
					pu.time = 0;
					pu.orgCaptialRent = nr;
					temporaryCapitalRent.add(nr);
					//pu.capitalRent = nr;
					pu.exp_inv_lambda_x_time = 1.0f;
				} else {
					temporaryCapitalRent.add(cr);
				}
			}
		}
		
		for( int i_y = 0; i_y < height; ++i_y){
			for( int i_x = 0; i_x < width; ++i_x){
				PropertyUnit pu = getPropertyUnit(i_x, i_y);
				pu.capitalRent = temporaryCapitalRent.get(i_y*width+i_x);
			}
		}
	}
	private void setPUDisplayValues(){
//		for(int i_x = 0; i_x < width; ++i_x){
//			for(int i_y = 0; i_y < height; ++i_y){
//				Grid2DPosition curPos = new Grid2DPosition(i_x, i_y);
//				PropertyUnit pu = getPropertyUnit(curPos);
//				super.putValue$atX$Y(normalizeRent(pu.capitalRent), i_x, i_y);
//			}
//		}
	}
	private void updateACR(){
		acr = 0.0f;
		for(int i_x = 0; i_x < width; ++i_x){
			for(int i_y = 0; i_y < height; ++i_y){
				PropertyUnit pu = getPropertyUnit(i_x, i_y);
				acr += pu.capitalRent;
			}
		}
		acr /= (width * height);
	}
	
	public float getNeighbourRent(Grid2DPosition pos){
		int neighbourCount = 0;
		float totalRent = 0.0f;
		
		int xStart = Math.max(0, calcStartPos(pos.x, model.neighbourRadius));
		int yStart = Math.max(0, calcStartPos(pos.y, model.neighbourRadius));
		int xEnd = Math.min(width - 1, calcEndPos(pos.x, model.neighbourRadius));
		int yEnd = Math.min(height - 1, calcEndPos(pos.y, model.neighbourRadius));
		
		Grid2DPosition curPos = new Grid2DPosition(0, 0);
		
		for( int i_x = xStart; i_x <= xEnd; ++i_x){
			for( int i_y = yStart; i_y <= yEnd; ++i_y){
				curPos.x = i_x;
				curPos.y = i_y;
				if (!farThan(pos, curPos, model.neighbourRadius)){
					++neighbourCount;
					totalRent += getPropertyUnit(curPos).capitalRent;
				}
			}
		}
		if( neighbourCount == 0){
			return 0.0f;
		}
		return totalRent / neighbourCount;
	}
	public float getConstructionCost(Grid2DPosition pos){
		PropertyUnit pu = getPropertyUnit(pos);
		return getConstructionCost(pu);
	}
	public float getConstructionCost(PropertyUnit pu){
		float cost = (float) (model.constructionCost * ( 1 - pu.exp_inv_lambda_x_time ));
		return cost;
	}
	public float getNeighbourGap(Grid2DPosition pos){
		return getNeighbourRent(pos) - getPropertyUnit(pos).capitalRent;
	}
	public PropertyUnit getPropertyUnit(Grid2DPosition pos){
		return pus.get(pos.y * width + pos.x);
	}
	public PropertyUnit getPropertyUnit(int x, int y){
		return pus.get(x + y * width);
	}
	
	public float getRentGap(Grid2DPosition pos){
		return 1 - ( getPropertyUnit(pos).capitalRent / getPropertyUnit(pos).potentialRent);
	}
	
	public float getACR(){
		return acr;
	}
	public List<Grid2DPosition> getNeedInvestedPUPositions(float threshold){
		List<Grid2DPosition> posList = new LinkedList<Grid2DPosition>();
		for(int i_x = 0; i_x < width; ++i_x){
			for(int i_y = 0; i_y < height; ++i_y){
				Grid2DPosition pos = new Grid2DPosition(i_x, i_y);
				if( getRentGap(pos) > threshold && this.getPropertyUnit(pos).time > 0){
					posList.add(pos);
				}
			}
		}
		return posList;
	}
	
	public void update(){
		decayPUs();
		rehabilitatePUs();
		setPUDisplayValues();
		updateACR();
	}
}
