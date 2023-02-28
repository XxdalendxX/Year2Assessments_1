using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Platform : MonoBehaviour
{
    [SerializeField] protected float TravelDistance;
    [SerializeField] protected float TravelTime;
    [SerializeField] protected bool awake = false;
    [SerializeField] protected bool complete = false;
    [SerializeField] protected Vector3 normal;
    [SerializeField] protected Vector3 velocity;
}
