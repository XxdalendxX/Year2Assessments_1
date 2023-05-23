using System.Collections;
using System.Collections.Generic;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;

public class CameraMovement : MonoBehaviour
{
    [SerializeField] Transform m_Camera;
    Vector3 camPos;
    Quaternion camRot;

    private void Awake()
    {
        infoTextL.gameObject.SetActive(false);
        infoTextR.gameObject.SetActive(false);
    }

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

    [SerializeField] TMP_Text infoTextL;
    public void InfoTextToggleL()
    {
        if (infoTextL.gameObject.activeSelf == false)
            infoTextL.gameObject.SetActive(true);
        else
            infoTextL.gameObject.SetActive(false);
    }

    [SerializeField] TMP_Text infoTextR;
    public void InfoTextToggleR()
    {
        if (infoTextR.gameObject.activeSelf == false)
            infoTextR.gameObject.SetActive(true);
        else
            infoTextR.gameObject.SetActive(false);
    }
}
