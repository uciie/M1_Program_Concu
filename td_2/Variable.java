public class Variable{
    private int x = 0;

    public synchronized void inc(int i){
        this.x += i;
    }

    public int getX(){
        return this.x;
    }

}