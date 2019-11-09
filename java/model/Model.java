package model;

public class Model {

    static {
	   System.loadLibrary("pinswrapper");
    }

    private native void load_model(String modelPath);
    public native int getStateLength();
    public native int[] getInitialState();
    public native int getNumberOfTransitions();
    public native int[][] getDM();
    public native void getNextState(int[] state);

    public Model(String modelPath){
	   load_model(modelPath);
    }

    private void next_state(int[] state){
        for (int e : state) {
            System.out.print(e + " ");
        }
        System.out.println("");
    }
}
