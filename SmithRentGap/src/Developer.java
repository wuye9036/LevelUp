import java.util.List;
import java.util.ListIterator;

import mas.math.vector.Grid2DPosition;

public class Developer {
	
	private ResearchArea area;
	private RentGapModelSwarm model;
	
	public Developer(ResearchArea area, RentGapModelSwarm model){
		this.area = area;
		this.model = model;
	}
	
	public void update(){
		float residualCapital = model.developerCapital; 
		//拷贝到数组中
		List<Grid2DPosition> puPosList = area.getNeedInvestedPUPositions(model.maintainceThreshold);
		int puCount = 0;
		Grid2DPosition[] puPosArray = new Grid2DPosition[puPosList.size()];
		
		for(ListIterator<Grid2DPosition> it = puPosList.listIterator(); it.hasNext();){
			Grid2DPosition puPos = (Grid2DPosition)it.next();
			puPosArray[puCount] = puPos;
			++puCount;
		}
		
		//重建地块
		while( residualCapital > 0.0f && puCount > 0){
			int randomPosIndex = Util.randomInt(0, puCount - 1);
			Grid2DPosition randomPos = puPosArray[randomPosIndex];
			float puConstructionCost = area.getConstructionCost(randomPos);
			
			if( residualCapital > puConstructionCost ){
				//如果资金足以支付随机选出的单元，那么就直接支付
				
				//reset property unit
				PropertyUnit randomPU = area.getPropertyUnit(randomPos);
				randomPU.time = 0;
				randomPU.orgCaptialRent = randomPU.potentialRent;
				randomPU.capitalRent = randomPU.orgCaptialRent;
				randomPU.exp_inv_lambda_x_time = 1.0;
				residualCapital -= puConstructionCost;
				
				//remove PU via move last element to current position
				puPosArray[randomPosIndex] = puPosArray[--puCount];
			} else {
				//否则运用快速排序法筛选掉高于资金总数的单元
				
				int leftFilterIndex = 0;
				int rightFilterIndex = puCount - 1;
				while(leftFilterIndex <= rightFilterIndex){
					Grid2DPosition leftPos = puPosArray[leftFilterIndex];
					float leftConstructionCost = area.getConstructionCost(leftPos);
					if (leftConstructionCost > residualCapital){
						while(true){
							if (leftFilterIndex > rightFilterIndex){
								break;
							}
							
							Grid2DPosition rightPos = puPosArray[rightFilterIndex];
							float rightConstructionCost = area.getConstructionCost(rightPos);
							if (rightConstructionCost <= residualCapital){
								swap(puPosArray, leftFilterIndex, rightFilterIndex);
								--rightFilterIndex;
								break;
							}
							--rightFilterIndex;
						}
					}
					++leftFilterIndex;
				}
				
				puCount = rightFilterIndex+1;
			}
		}
	}
	private <T extends Object> void swap(T[] array, int lhsIdx, int rhsIdx){
		T tmpObj = array[lhsIdx];
		array[lhsIdx] = array[rhsIdx];
		array[rhsIdx] = tmpObj;
	}
}
