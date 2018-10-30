public class Request {
    int floor;
    int dir;

    public Request(int floor, int dir) {
        this.floor = floor;
        this.dir = dir;
    }

    public boolean equals(Request r) {
        return floor == r.floor && dir == r.dir;
    }

    @Override
    public String toString() {
        return "{" +
                "floor=" + floor +
                ", dir=" + dir +
                '}';
    }
}

