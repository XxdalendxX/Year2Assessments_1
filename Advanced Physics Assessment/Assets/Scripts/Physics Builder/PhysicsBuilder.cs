using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//abstract object that creates a series
public class PhysicsBuilder : MonoBehaviour
{
    [Tooltip("A prefab that we can clone several times as children of this object.")]
    [SerializeField] PhysicsBuilderPart prefab;

    [Space]
    [SerializeField] float breakingForce = 0;

    [Tooltip("How many times will the prefab be cloned")]
    [SerializeField] int count;

    [Tooltip("Offset in local space of this object for positioning each child")]
    [SerializeField] Vector3 offset;

    bool fixStart;
    bool fixEnd;

   [ContextMenu("Build")]
   void Build()
    {
        //delete any old ones
        foreach (Rigidbody rb in gameObject.GetComponentsInChildren<Rigidbody>())
            DestroyObj(rb.gameObject);

        if (prefab == null) { return; }

        PhysicsBuilderPart previous = null;

        for (int i = 0; i < count; i++)
        {
            //clone the prefab and make it a child of the object
            PhysicsBuilderPart instance = Instantiate(prefab, transform);

            instance.transform.localPosition = i * offset;
            instance.transform.localRotation = prefab.transform.localRotation;
            instance.name = name + "_" + i;

            Rigidbody rb = instance.GetComponent<Rigidbody>();

            rb.isKinematic = ((i == 0 && fixStart) || (i == count - 1 && fixEnd));

            //attach the previous body to this one
            if(previous)
            {
                foreach (Joint joint in previous.forwardJoints)
                {
                    joint.connectedBody = rb;
                }
            }

            previous = instance;
        }
    }

    [ContextMenu("Set Break Force")]
    public void SetBreakingForce()
    {
        if (breakingForce != 0)
        {
            //foreach (Joint joint in GetComponentInChildren<Joint>())
            {
                //joint.breakForce = breakingForce;
            }
        }   
    }

    void DestroyObj(Object obj)
    {
        if (Application.isPlaying)
            Destroy(obj);
        else
            DestroyImmediate(obj);
    }

}
