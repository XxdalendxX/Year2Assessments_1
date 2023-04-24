using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class spin : MonoBehaviour
{
    public bool switchRotation = false;
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if(switchRotation == false)
        {
            clockwise();
        }
        else
        {
            anticlockwise();
        }
    }

    void clockwise()
    {
        this.transform.Rotate(0, 0.1f, 0);
    }

    void anticlockwise()
    {
        this.transform.Rotate(0, -0.1f, 0);
    }
}
