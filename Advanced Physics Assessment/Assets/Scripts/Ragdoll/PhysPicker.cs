using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PhysPicker : MonoBehaviour
{
    [SerializeField] Camera cam;
    [SerializeField, Range(0,100000)]float force = 5f;
    [SerializeField] int layerMask;

    // Start is called before the first frame update
    void Start()
    {
        cam = GetComponent<Camera>();
        string[] layers = { "Default" };
        layerMask = LayerMask.GetMask(layers);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            RaycastHit hit;
            Ray ray = cam.ScreenPointToRay(Input.mousePosition);
            if (Physics.Raycast(ray, out hit, Mathf.Infinity, layerMask))
            {
               Ragdoll ragdoll = hit.collider.GetComponent<Ragdoll>();
               if (ragdoll)
               {
                    ragdoll.RagdollOn = true;
               }

                Rigidbody body = hit.collider.GetComponent<Rigidbody>();
                if(body)
                {
                    body.AddForce(ray.direction * force);
                }
            }
        }
    }
}
