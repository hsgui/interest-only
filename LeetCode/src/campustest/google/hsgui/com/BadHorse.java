package campustest.google.hsgui.com;

import java.io.File;
import java.io.PrintWriter;
import java.util.*;

/**
 * Created with IntelliJ IDEA.
 * https://code.google.com/codejam/contest/2933486/dashboard#s=p0
 * User: hsgui
 * Date: 13-9-14
 * Time: 下午3:47
 * To change this template use File | Settings | File Templates.
 */
public class BadHorse {
    private Map<String, Integer> name2Index = null;
    int nameCount = 0;
    LinkedList<Integer>[] adjs = null;
    int[] groupId = null;

    public static void main(String[] args) throws Exception {
        BadHorse badHorse = new BadHorse();
        badHorse.run();
    }

    public void run() throws Exception{
        String path = BadHorse.class.getClassLoader().getResource("").toURI().getPath().substring(1);
        Scanner in = new Scanner(new File(path + "A.in"));
        PrintWriter out = new PrintWriter(new File(path + "A.out"));
        int testCount = new Integer(in.nextLine());
        for (int i = 0; i < testCount; i++){
            buildGraph(in);
            boolean result = true;
            for (int j = 0; j < nameCount; j++){
                if (groupId[j] == 0){
                    groupId[j] = 1;
                    result = bfs(j);
                    if (result == false){
                        out.printf("Case #%d: No\n", i+1);
                        break;
                    }
                }
            }
            if (result == true){
                out.printf("Case #%d: Yes\n", i+1);
            }
        }
        out.flush();
        out.close();
        in.close();
    }

    public void buildGraph(Scanner in){
        int edgeCount = new Integer(in.nextLine());
        nameCount = 0;
        name2Index = new HashMap<String, Integer>();
        adjs = new LinkedList[edgeCount + 1];
        groupId = new int[edgeCount+1];

        for (int i=0; i < edgeCount; i++){
            String twoNames = in.nextLine();
            String[] names = twoNames.split(" ");
            if (!name2Index.containsKey(names[0])){
                name2Index.put(names[0], nameCount);
                nameCount++;
            }
            if (!name2Index.containsKey(names[1])){
                name2Index.put(names[1], nameCount);
                nameCount++;
            }
            int firstNameIndex = name2Index.get(names[0]);
            int secondNameIndex = name2Index.get(names[1]);
            if (adjs[firstNameIndex] == null){
                adjs[firstNameIndex] = new LinkedList<Integer>();
            }
            if (adjs[secondNameIndex] == null){
                adjs[secondNameIndex] = new LinkedList<Integer>();
            }
            adjs[firstNameIndex].add(secondNameIndex);
            adjs[secondNameIndex].add(firstNameIndex);
        }
    }

    public boolean bfs(int nameIndex){
        Queue<Integer> queue = new LinkedList<Integer>();
        queue.add(nameIndex);
        while (!queue.isEmpty()){
            int index = queue.remove();
            for (int adj : adjs[index]){
                if(groupId[adj] == 0){
                    if (groupId[index] == 1){
                        groupId[adj] = 2;
                    }else if (groupId[index] == 2){
                        groupId[adj] = 1;
                    }
                    queue.add(adj);
                }else if (groupId[adj] == groupId[index]){
                    return false;
                }
            }
        }
        return true;
    }
}
