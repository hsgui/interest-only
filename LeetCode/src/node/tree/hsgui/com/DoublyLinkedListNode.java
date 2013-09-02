package node.tree.hsgui.com;

/**
 * Created with IntelliJ IDEA.
 * User: hsgui
 * Date: 13-9-2
 * Time: 上午10:16
 * To change this template use File | Settings | File Templates.
 */
public class DoublyLinkedListNode {
    public Object value;
    public DoublyLinkedListNode previous;
    public DoublyLinkedListNode next;

    public DoublyLinkedListNode(Object value)
    {
        this.next = this;
        this.previous = this;
        this.value = value;
    }
}
