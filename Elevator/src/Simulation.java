public class Simulation {
    private final int floorCount = 10;
    static final int UP = 1, STAY = 0, DOWN = -1, FREQUENCY = 50;
    static final double T = 1200, interval = 1;
    public int time;
    private final double[] elevatorX = {0.6, 0.85};
    public Elevator[] elevators;
    public Floor[] floors;
    private String human = "./human.png", reversed = "./reversed.png";

    public void callRemoveRequest(int i, Request r) {
        elevators[i].removeDest(r);
    }

    public void arrival(int i, Floor f) {
        System.out.println("[LOG]@" + time +" Elevator " + i + " arrives at " + f.floorNum);
        elevators[i].onArrival(f);
        f.peopleGoInTo(elevators[i]);
        System.out.println("[INFO}@" + time + " Elevator " + i + " will stay " + elevators[i].stayTime + " seconds.");
    }

    public int actualDistance(Elevator e, Request r) {
        int highest = e.highestDest();
        if (e.dir == Simulation.STAY || (e.dir == r.dir && (r.floor - e.curFloor) * e.dir > 0)) {
            return Math.abs(e.curFloor - r.floor);
        } else if(e.dir != r.dir) {
            return Math.abs(highest - e.curFloor) + Math.abs(highest - r.floor);
        } else  {
            return 16 - Math.abs(e.curFloor - r.floor);
        }
    }

    public void chooseElevator(Request r) {
        int d1 = actualDistance(elevators[0], r), d2 = actualDistance(elevators[1], r);
        System.out.println("[CHOOSE]d1 is " + d1 + ", d2 is " + d2);
        if (d1 > 13 && d2 > 13) {
            elevators[0].addDest(r);
            elevators[1].addDest(r);
            return;
        }
        if (d1 < d2) {
            elevators[0].addDest(r);
        } else {
            elevators[1].addDest(r);
        }
    }

    public void click(Request r) {
        System.out.println("[LOG]@" + time +" " + r.floor + "th floor click: " + r.dir);
        chooseElevator(r);
    }

    public Simulation() {
        this.time = 0;
        this.elevators = new Elevator[2];
        for (int i = 0; i < 2; i++) {
            elevators[i] = new Elevator(i, elevatorX[i], this);
        }
        this.floors =  new Floor[floorCount - 1];
        for (int i = 0; i < floorCount - 1; i++) {
            floors[i] = new Floor(i + 2, this);
        }
        this.floors[0].hasArrived[0] = this.floors[0].hasArrived[1] = false;
    }

    public void drawBackground() {
        StdDraw.line(0.5, 0.1, 0.5, 1);
        StdDraw.line(0.75, 0.1, 0.75, 1);
        for (int i = 1; i < floorCount; i++) {
            double height = i * 0.1;
            StdDraw.line(0.1, height, 0.5, height);
            StdDraw.text(0.03, height + 0.05, (i+1) + "F");
        }
    }

    public void drawPeople(LinkedListDeque<Person> people, String picture) {
        int ithCount = people.size();
        for (int j = 0; j < ithCount; j++) {
            Person jth = people.get(j);
            if (picture.equals(reversed) && jth.xPos > 0.4) {
                return;
            }
            StdDraw.picture(jth.xPos, jth.yPos, picture);
            StdDraw.text(jth.xPos, jth.yPos + 0.03, jth.destination + "");
        }
    }

    public void draw() {
        StdDraw.clear();
        drawBackground();
        for (int i = 0; i < floorCount - 1; i++) {
            drawPeople(floors[i].upPeople, human);
            drawPeople(floors[i].downPeople, human);
            drawPeople(floors[i].outPeople, reversed);
        }
        for (int i = 0; i < 2; i++) {
            double x = elevators[i].xPos;
            double y = elevators[i].yPos;
            StdDraw.text(x, y, elevators[i].count() + "");
            StdDraw.rectangle(x, y, Elevator.halfWidth, Elevator.halfHeight);
        }
        StdDraw.show();
        StdDraw.pause(8);
    }

    public void run() {
        for(time = 0; time < T; time += interval) {
            System.out.println();
            System.out.println("[TIME]" + time);
            for (int i = 0; i < 2; i++) {
                Elevator e = elevators[i];
                if (!e.dests.isEmpty() && e.curFloor == e.nextStop && (e.stayTime == -1)) {
                    arrival(i, floors[e.curFloor - 2]);
                }
                System.out.println("[INFO]@" + time + " Elevator" + i +" dir:" + e.dir + " Floor: " + e.curFloor + " yPos: " + e.yPos);
                e.dests.printDeque();
                System.out.println(e.count() + " people inside elevator" + i);
                e.people.printDeque();
            }
            for (int i = 0; i < floorCount - 1; i++) {
                floors[i].addPerson();
            }
            for (int i = 0; i < FREQUENCY; i++) {
                draw();
                for (int j = 0; j < floorCount - 1; j++) {
                    floors[j].move();
                }
                for (int j = 0; j < 2; j++) {
                    elevators[j].move();
                }
            }
            for (int i = 0; i < 2; i++) {
                Elevator e = elevators[i];
                if (e.doorOpening > 0) {
                    System.out.println("[DOOR]@" + time + " Elevator " + e.ID + " door opening.");
                    e.doorOpening -= 1;
                }
                if (e.goingOut > 0) {
                    e.goingOut -= 1;
                    System.out.println("[OUT] " + " Elevator " + e.ID + " remaining " + e.goingOut);
                }
                if (e.stayTime < 0 && e.nextStop != e.curFloor) {
                    e.curFloor += e.dir;
                }
                e.yPos = e.curFloor * 0.1 - 0.05;
                if (e.stayTime >= 0) {
                    System.out.println("[GOIN] " + " People at floor " + e.curFloor);
                    floors[e.curFloor - 2].upPeople.printDeque();
                    floors[e.curFloor - 2].downPeople.printDeque();
                    if (e.stayTime == 0) {
                        Floor f = floors[e.curFloor - 2];
                        f.hasArrived[i] = false;
                        System.out.println("[LOG]@" + time + "elevator " + i + "leaves floor " + e.curFloor);
                        e.calcNextStop();
                        e.doorClosed = true;
                        if (e.dir == 1 && !f.upPeople.isEmpty()) {
                            click(new Request(f.floorNum, e.dir));
                        }
                        if (e.dir == -1 && !f.downPeople.isEmpty()) {
                            click(new Request(f.floorNum, e.dir));
                        }
                        f.reorganize();
                    }
                    e.stayTime -= 1;
                }
            }
        }
    }

    public static void main(String[] args) {
        Simulation simulator = new Simulation();
        StdDraw.enableDoubleBuffering();
        StdDraw.setCanvasSize(900, 700);
        simulator.drawBackground();
        simulator.run();
    }
}
