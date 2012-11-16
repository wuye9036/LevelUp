import swarm.Globals;
import swarm.Selector;
import swarm.activity.ActionGroup;
import swarm.activity.ActionGroupImpl;
import swarm.activity.Activity;
import swarm.activity.Schedule;
import swarm.activity.ScheduleImpl;
import swarm.analysis.EZGraph;
import swarm.analysis.EZGraphImpl;
import swarm.defobj.Zone;
import swarm.gui.Colormap;
import swarm.gui.ColormapImpl;
import swarm.gui.ZoomRaster;
import swarm.gui.ZoomRasterImpl;
import swarm.objectbase.EmptyProbeMapImpl;
import swarm.objectbase.MessageProbe;
import swarm.objectbase.Swarm;
import swarm.objectbase.VarProbe;
import swarm.simtoolsgui.GUISwarmImpl;
import swarm.space.Value2dDisplay;
import swarm.space.Value2dDisplayImpl;

public class RentGapObserverSwarm extends GUISwarmImpl {
	public ActionGroup displayActions;
	public Schedule displaySchedule;
	public RentGapModelSwarm modelSwarm;
	
	public Colormap colormap;
	public ZoomRaster worldRaster;
	public EZGraph rentGraph;

	public Value2dDisplay rentDisplay;
	
	public RentGapObserverSwarm(Zone zone, ExperimentRecorder expRec){
		super(zone);
	}

	public Object _worldRasterDeath_ (Object caller){
		worldRaster.drop();
		worldRaster = null;
		return this;
	}

	public Object _rentGraphDeath_ (Object caller){
		rentGraph.drop();
		rentGraph = null;
		return this;
	}

    class RentGapObserverProbeMap extends EmptyProbeMapImpl {
        private VarProbe probeVariable (String name) {
          return
            Globals.env.probeLibrary.getProbeForVariable$inClass
            (name, RentGapObserverSwarm.this.getClass ());
        }
        private MessageProbe probeMessage (String name) {
          return
            Globals.env.probeLibrary.getProbeForMessage$inClass
            (name, RentGapObserverSwarm.this.getClass ());
        }
        
        @SuppressWarnings("unused")
		private void addVar (String name) {
          addProbe (probeVariable (name));
        }
        
        @SuppressWarnings("unused")
		private void addMessage (String name) {
          addProbe (probeMessage (name));
        }
        
        @SuppressWarnings("unchecked")
		public RentGapObserverProbeMap (Zone _aZone, Class aClass) {
          super (_aZone, aClass);
        }
      }
    
	public Object buildObjects(){
		super.buildObjects();
		
		modelSwarm = new RentGapModelSwarm(getZone());

		Globals.env.createArchivedProbeDisplay(modelSwarm, "modelSwarm");
		//Globals.env.createArchivedProbeDisplay(this, "observerSwarm");

		getControlPanel().setStateStopped();

		modelSwarm.buildObjects();

		colormap = new ColormapImpl( getZone() );
		for(int colorVal = 0; colorVal < 128; ++colorVal){
			colormap.setColor$ToRed$Green$Blue((byte)colorVal, (double) colorVal / 127.0, 0, 0);
		}

		worldRaster = new ZoomRasterImpl (getZone (), "worldRaster");
		try {
			worldRaster.enableDestroyNotification$notificationMethod 
			(this,
					new Selector (getClass (), "_worldRasterDeath_", false));
		} catch (Exception e) {
			System.err.println ("Exception _worldRasterDeath_: " 
					+ e.getMessage ());
		}

		worldRaster.setColormap(colormap);
		worldRaster.setZoomFactor(4);
		worldRaster.setWidth$Height(64, 64);
		worldRaster.setWindowTitle("Rent Gap Simulation");
		worldRaster.pack();

		rentDisplay = new Value2dDisplayImpl(getZone(), worldRaster, colormap, modelSwarm.area);
		rentDisplay.setDisplayMappingM$C(1, 0);

		rentGraph = new EZGraphImpl(getZone(), "Average Captial Rent", "Time", "ACR", "ACR Graph");
		try {
			rentGraph.enableDestroyNotification$notificationMethod 
			(this, new Selector (getClass (),
					"_rentGraphDeath_",
					false));
		} catch (Exception e) {
			System.err.println ("Exception _rentGraphDeath_: " 
					+ e.getMessage ());
		}

		try{
			rentGraph.createSequence$withFeedFrom$andSelector("ACR", modelSwarm.area, new Selector(Class.forName("ResearchArea"), "getACR", false));
		} catch(Exception e){
			System.err.println("Exception getACR: " + e.getMessage());
		}

		return this;
	}

	public Object _update_(){
		if (worldRaster != null){
			rentDisplay.display();
			worldRaster.drawSelf();
		}

		if( rentGraph != null){
			rentGraph.step();
		}

		return this;
	}

	public Object buildActions(){
		super.buildActions();
		modelSwarm.buildActions();

		displayActions = new ActionGroupImpl(getZone());
		try{
			displayActions.createActionTo$message(this, new Selector(this.getClass(), "_update_", false));
			displayActions.createActionTo$message(Globals.env.probeDisplayManager, new Selector(Globals.env.probeDisplayManager.getClass(), "update", true));
			displayActions.createActionTo$message(getActionCache(), new Selector(getActionCache().getClass(), "doTkEvents", true));
		} catch (Exception e){
			System.err.println("Exception doTkEvent or probeDisplayManager: " + e.getMessage());
		}
		displaySchedule = new ScheduleImpl(getZone(), 1);
		displaySchedule.at$createAction(0, displayActions);

		return this;
	}

	public Activity activateIn (Swarm swarmContext) {
		super.activateIn (swarmContext);
		modelSwarm.activateIn (this);
		displaySchedule.activateIn (this);

		return getActivity();
	}
	
	public void drop () {
		if (rentGraph != null)
			rentGraph.disableDestroyNotification ();
		if (worldRaster != null)
			worldRaster.disableDestroyNotification ();
		super.drop ();
	}
}
