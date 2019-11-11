package model;

import java.util.Objects;

public class State {
	private int[] places;

	public State(int[] places) {
		this.places = places;
	}

	public int[] getStateAsArray(){
		return places;
	}
	
    @Override
    public boolean equals(Object o) {

        if (o == this) return true;
        if (!(o instanceof State)) {
            return false;
        }
        State state = (State)o;        
        for (int i = 0; i < places.length; i++) {
			if(places[i] != state.places[i]) return false; 
		}
        return true;        
    }

    @Override
    public int hashCode() {
        return Objects.hash(places);
    }
}
