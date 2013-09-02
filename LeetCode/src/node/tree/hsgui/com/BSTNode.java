package node.tree.hsgui.com;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-2
 * Time: 上午10:51
 * To change this template use File | Settings | File Templates.
 */
public class BSTNode {
    public Object value;
    public BSTNode left;
    public BSTNode right;

    public BSTNode(Object value)
    {
        this.value = value;
        left = null;
        right = null;
    }

    @Override
    public String toString() {
        return value.toString();
    }
}
