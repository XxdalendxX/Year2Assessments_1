using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

public class CameraMovement : MonoBehaviour
{
    [SerializeField] Transform m_Camera;
    Vector3 camPos;
    Quaternion camRot;


    private void Update()
    {
        camPos = m_Camera.position;
        camRot = m_Camera.rotation;
    }
    public void CameraLeft()
    {
        Vector3 position;
        Vector3 rotation;

        if (camPos.x == 0)
        {
            if(camPos.z == 10)
            {
                position = new Vector3(camPos.x + 10, camPos.y, camPos.z - 10);
                rotation = new Vector3(camRot.x, camRot.y + 90, camRot.z);
            }
            else
            {
                position = new Vector3(camPos.x - 10, camPos.y, camPos.z + 10);
                rotation = new Vector3(camRot.x, camRot.y + 90, camRot.z);
            }
        }
        else 
        {
            if(camPos.x == 10)
            {
                position = new Vector3(camPos.x - 10, camPos.y, camPos.z - 10);
                rotation = new Vector3(camRot.x, camRot.y + 90, camRot.z);
            }
            else
            {
                position = new Vector3(camPos.x + 10, camPos.y, camPos.z + 10);
                rotation = new Vector3(camRot.x, camRot.y + 90, camRot.z);
            }
        }

        Vector3 oldPos = m_Camera.transform.position;
        m_Camera.position = Vector3.Lerp(oldPos, position, 10);
        m_Camera.Rotate(rotation);
        
    }

    public void CameraRight()
    {
        Vector3 position;
        Vector3 rotation;

        if (camPos.x == 0)
        {
            if (camPos.z == 10)
            {
                position = new Vector3(camPos.x - 10, camPos.y, camPos.z - 10);
                rotation = new Vector3(camRot.x, camRot.y - 90, camRot.z);
            }
            else
            {
                position = new Vector3(camPos.x + 10, camPos.y, camPos.z + 10);
                rotation = new Vector3(camRot.x, camRot.y - 90, camRot.z);
            }
        }
        else
        {
            if (camPos.x == 10)
            {
                position = new Vector3(camPos.x - 10, camPos.y, camPos.z + 10);
                rotation = new Vector3(camRot.x, camRot.y - 90, camRot.z);
            }
            else
            {
                position = new Vector3(camPos.x + 10, camPos.y, camPos.z - 10);
                rotation = new Vector3(camRot.x, camRot.y - 90, camRot.z);
            }
        }

        Vector3 oldPos = m_Camera.transform.position;
        m_Camera.position = Vector3.Lerp(oldPos, position, 10);
        m_Camera.Rotate(rotation);

    }
}
