package node.tree.hsgui.com;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-3
 * Time: 下午2:56
 * To change this template use File | Settings | File Templates.
 */
public class SingleLinkedListNode {
    public Object value;
    public SingleLinkedListNode next;

    public SingleLinkedListNode(Object value)
    {
        this.value = value;
        next = null;
    }
}
