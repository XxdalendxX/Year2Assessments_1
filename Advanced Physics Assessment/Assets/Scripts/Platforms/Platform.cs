using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platform : MonoBehaviour
{
    [SerializeField]
    Transform startPos, endPos;
    [SerializeField] float speed = 3f;
    [SerializeField] bool _switch = false;
    [SerializeField] GameObject player = null;

 
    [SerializeField] Vector3 velocity;

    private void FixedUpdate()
    {
        Vector3 initialPosition = transform.position;
        Vector3 finalPosition;
        if (!_switch)
        {
            transform.position = Vector3.MoveTowards(transform.position, endPos.position, speed * Time.fixedDeltaTime);
            finalPosition = transform.position;
            velocity = GetVelocity(initialPosition, finalPosition);
            if (player != null) { player.transform.position = Vector3.MoveTowards(player.transform.position, finalPosition, speed * Time.fixedDeltaTime); }
        }
        else if (_switch)
        {
            transform.position = Vector3.MoveTowards(transform.position, startPos.position, speed * Time.fixedDeltaTime);
            finalPosition = transform.position;
            velocity = GetVelocity(initialPosition, finalPosition);
            if (player != null) { player.transform.position = Vector3.MoveTowards(player.transform.position, finalPosition, speed * Time.fixedDeltaTime); }
        }

            if (transform.position == endPos.position)
                _switch = true;
            else if (transform.position == startPos.position)
                _switch = false;

    }

    private void OnTriggerEnter(Collider other)
    {
       if (other.CompareTag("Player"))
       {
            other.transform.parent = this.transform;
            player = other.gameObject;
       }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            other.transform.parent = null;
            player = null;
        }
    }

    private Vector3 GetVelocity(Vector3 initialPosition, Vector3 finalPosition)
    {
        return (finalPosition - initialPosition) / Time.fixedDeltaTime;
    }
}
