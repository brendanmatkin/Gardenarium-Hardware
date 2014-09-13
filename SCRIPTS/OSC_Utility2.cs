// Converted from UnityScript to C# at http://www.M2H.nl/files/js_to_c.php - by Mike Hergaarden
// Do test the code! You usually need to change a few small bits.

using UnityEngine;
using System.Collections;

public class OSC_Utility2 : MonoBehaviour {
	private string UDPHost = "127.0.0.1";
	private int listenerPort = 9000;
	private int broadcastPort = 9001;
	[HideInInspector]
	public Osc oscHandler;
	//[HideInInspector]
	//public Destroypop2 pop;

	private int counter = 0;


	public void Start(){	
		UDPPacketIO udp = GetComponent<UDPPacketIO>();
		print("osc!");
		udp.init(UDPHost, broadcastPort, listenerPort);
		oscHandler = GetComponent<Osc>(); 
		oscHandler.init(udp);
		print("Running");
	}


	public void  Update (){
		Destroypop2 destroypop2 = GetComponentInChildren<Destroypop2>();
		//Destroypop3 destroypop3 = GetComponentInChildren<Destroypop3>();
		bool vender = destroypop2.vend;
		// bool vender3 = destroypop3.vend;
		if(vender == true) oscHandler.Send(Osc.StringToOscMessage("/vend 1"));
		//if(vender3 == true) oscHandler.Send(Osc.StringToOscMessage("/vend 1"));
		destroypop2.vend = false;
		//destroypop3.vend = false;
	}	

}