using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerTriggeredRaisingPlatform : Platform
{
    float distance;
    float time;
    float initialVelocity;
    float finalVelocity;
    float acceleration;


    // Start is called before the first frame update
    void Start()
    {
        distance = TravelDistance;
        time = TravelTime;
        finalVelocity = 0;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
         
        if(awake && !complete)
        {
            gameObject.transform.position += velocity;
            velocity.y += acceleration * Time.fixedDeltaTime * normal.y;
            velocity.x += acceleration * Time.fixedDeltaTime * normal.x;
            velocity.z += acceleration * Time.fixedDeltaTime * normal.z;
            if(initialVelocity > 0 && velocity.x < 0 && velocity.y < 0 && velocity.z < 0)
            {
                complete = true;
            }
            else if (initialVelocity < 0 && velocity.x > 0 && velocity.y > 0 && velocity.z > 0)
            {
                complete = true;
            }

        }
        else if(complete == false)
        {
            initialVelocity = 2 * (distance / time);
            acceleration = (finalVelocity - initialVelocity) / time;
            velocity.y = initialVelocity * normal.y;
            velocity.x = initialVelocity * normal.x;
            velocity.z = initialVelocity * normal.z;
            awake = true;
        }
    }

    void OnControllerColliderHit(ControllerColliderHit hit)
    {
        if(hit.gameObject.tag == "Player" && !awake)
        {
            initialVelocity = 2 * (distance / time);
            acceleration = (finalVelocity-initialVelocity) / time;
            awake = true;
        }
    }
}
