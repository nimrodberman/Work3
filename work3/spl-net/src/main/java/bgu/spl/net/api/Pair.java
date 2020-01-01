package bgu.spl.net.api;

public class Pair {

    private String K;
    private String V;

    public Pair(String h, String k) {
        K = h;
        V = k;
    }

    public String getK() {
        return K;
    }

    public String getV() {
        return V;
    }

    public void setK(String k) {
        K = k;
    }

    public void setV(String v) {
        V = v;
    }
}