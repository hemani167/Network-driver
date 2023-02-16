#include <linux/module.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/inetdevice.h>
#define DUMMY_DEVICE_NAME "dummy0"

static int dummy_open(struct net_device *dev)
{
    printk(KERN_ALERT"dummy 0 open and queue started");
    netif_start_queue(dev);
    return 0;
}

static int dummy_stop(struct net_device *dev)
{
    printk(KERN_ALERT"dummy 0 stop and queue closed");
    netif_stop_queue(dev);
    return 0;
}

static netdev_tx_t dummy_start_xmit(struct sk_buff *skb,
                                    struct net_device *dev)
{
    dev_kfree_skb(skb);
    return NETDEV_TX_OK;
}

static const struct net_device_ops dummy_device_ops = {
    .ndo_open = dummy_open,
    .ndo_stop = dummy_stop,
    .ndo_start_xmit = dummy_start_xmit,
};

static void dummy_setup(struct net_device *dev)
{
    ether_setup(dev);
    //inet_init_net(dev, &init_net);
    dev->netdev_ops = &dummy_device_ops;
}
struct net_device *dummy_dev;

static int __init dummy_init(void)
{
    
    int err;

    dummy_dev = alloc_netdev(0, DUMMY_DEVICE_NAME, dummy_setup);
    if (!dummy_dev)
        return -ENOMEM;

    err = register_netdev(dummy_dev);
    if (err) {
        free_netdev(dummy_dev);
        return err;
    }

    return 0;

}

static void __exit dummy_exit(void)
{
    unregister_netdev(dummy_dev);
    free_netdev(dummy_dev);
}

module_init(dummy_init);
module_exit(dummy_exit);

MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Dummy Network Driver");
MODULE_LICENSE("GPL");
