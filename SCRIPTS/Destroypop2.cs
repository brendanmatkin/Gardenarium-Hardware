using UnityEngine;
using System.Collections;

public class Destroypop2 : MonoBehaviour
	
{
	[HideInInspector]
	public bool vend = false; 

	void OnTriggerEnter(Collider other) 
	{
		vend = true;
		Destroy (gameObject, 1.5f);
		
	}
}

