package model;

public class Model {

    static {
	   System.loadLibrary("pinswrapper");
    }

    private String modelPath;
    private long model_t_ptr;
    private int stateLength;
    private int numOfTransitions;
    private int[][] dependencyMatrix;

    private native void load_model(String modelPath);
    private native int[] get_initial_state(long model_t_ptr);
    private native int get_next_state(long model_t_ptr, int transition, int[] state);

    public Model(String modelPath){
        this.modelPath = modelPath;
	    load_model(modelPath);
        /*System.out.println(model_t_ptr);
        System.out.println("length: " + stateLength);
        System.out.println("number of transitions: " + numOfTransitions);*/
        for (int[] ia : dependencyMatrix) {
            for (int e : ia) {
                System.out.print(e);                
            }
            System.out.println();
        }
    }

    public int getStateLength(){
        return stateLength;
    }

    public int getNumOfTransitions(){
        return numOfTransitions;
    }

    public int[] getInitialState(){
        return get_initial_state(model_t_ptr);
    }

    public int getNextState(int transition, int[] state){
        return get_next_state(model_t_ptr, transition, state);
    }

    private void nextState(int[] nextState){
        /*for (int e : nextState) {
            System.out.print(e);
        }*/
    }
}
