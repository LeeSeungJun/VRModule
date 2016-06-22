

#pragma once
#include "Runtime/Online/OnlineSubsystemVRils/Public/OnlineBeaconClient.h"
#include "VRServerBeaconClient.h"
#include "VRReplicatedMapInfo.h"
#include "VRServerBeaconLobbyClient.generated.h"


/**
* This because allows the 
*/
UCLASS(transient, notplaceable, config = Engine)
class UNREALTOURNAMENT_API AVRServerBeaconLobbyClient : public AOnlineBeaconClient
{
	GENERATED_UCLASS_BODY()

//	virtual FString GetBeaconType() override { return TEXT("VRLobbyBeacon"); }

	virtual void InitLobbyBeacon(FURL LobbyURL, uint32 LobbyInstanceID, FGuid InstanceGUID, FString AccessKey);
	virtual void OnConnected();
	virtual void OnFailure();
	
	virtual void UpdateMatch(const FMatchUpdate& MatchUpdate);
	virtual void UpdatePlayer(FUniqueNetIdRepl PlayerID, const FString& PlayerName, int32 PlayerScore, bool bSpectator, uint8 TeamNum, bool bLastUpdate, int32 PlayerRank, FName Avatar);
	virtual void EndGame(const FMatchUpdate& FinalMatchUpdate);
	virtual void Empty();

	/**
	 *	NotifyInstanceIsReady will be called when the game instance is ready.  It will replicate to the lobby server and tell the lobby to have all of the clients in this match transition
	 **/
	UFUNCTION(server, reliable, WithValidation)
	virtual void Lobby_NotifyInstanceIsReady(uint32 InstanceID, FGuid InstanceGUID, const FString& MapName);

	/**
	 * Tells the Lobby to update it's description on the stats
	 **/
	UFUNCTION(server, reliable, WithValidation)
	virtual void Lobby_UpdateMatch(uint32 InstanceID, const FMatchUpdate& MatchUpdate);

	/**
	 *	Allows the instance to update the lobby regarding a given player.
	 **/
	UFUNCTION(server, reliable, WithValidation)
	virtual void Lobby_UpdatePlayer(uint32 InstanceID, FUniqueNetIdRepl PlayerID, const FString& PlayerName, int32 PlayerScore, bool bSpectator, uint8 TeamNum, bool bLastUpdate, int32 PlayerRank, FName Avatar);

	/**
	 *	Tells the Lobby that this instance is at Game Over
	 **/
	UFUNCTION(server, reliable, WithValidation)
	virtual void Lobby_EndGame(uint32 InstanceID, const FMatchUpdate& MatchUpdate);

	/**
	 *	Tells the Lobby server that this instance is empty and it can be recycled.
	 **/
	UFUNCTION(server, reliable, WithValidation)
	virtual void Lobby_InstanceEmpty(uint32 InstanceID);


	/**
	 *	When we connect, if this is a connection between a hub and a dedicated instance, this function
	 * will be called to let the hub know I want to be a dedicated instance.
	 **/
	UFUNCTION(server, reliable, WithValidation)
	virtual void Lobby_IsDedicatedInstance(FGuid InstanceGUID, const FString& InHubKey, const FString& ServerName, const FString& ServerGameMode, const FString& ServerDescription, int32 MaxPlayers, bool bTeamGame);

	/**
	 *	Called from the hub, this will let a dedicated instance know it's been aVRhorized and is connected to 
	 *  the Hub.
	 **/
	UFUNCTION(client, reliable)
	virtual void AVRhorizeDedicatedInstance(FGuid HubGuid, int32 InstanceID);

	// Will cause the hub to prime the AllowedMapPackages list with all maps available on the server.
	UFUNCTION(server, reliable, withvalidation)
	virtual void Lobby_PrimeMapList(int32 InstanceID);

	UFUNCTION(client, reliable)
	virtual void Instance_ReceiveMap(const FString& MapPackageName, const FString& MapTitle, const FString& MapScreenshotReference, int32 Index);

	UFUNCTION(server, reliable, withvalidation)
	virtual void Lobby_SendNextMap(int32 LastIndex);

	UFUNCTION(client, reliable)
	virtual void Instance_ReceiveHubID(FGuid HubGuid);

	UFUNCTION(client, reliable)
	virtual void Instance_ReceieveRconMessage(const FString& TargetUniqueId, const FString& AdminMessage);

	UFUNCTION(client, reliable)
	virtual void Instance_ReceiveUserMessage(const FString& TargetUniqueId, const FString& Message);

	UFUNCTION(client, reliable)
	virtual void Instance_ForceShVRdown();

	UFUNCTION(client, reliable)
	virtual void Instance_Kick(const FString& TargetUniqueId);

	UFUNCTION(client, reliable)
	virtual void Instance_AVRhorizeAdmin(const FString& AdminId, bool bIsAdmin);

protected:

	// Will be set to true when the game instance is empty and has asked the lobby to kill it
	bool bInstancePendingKill;

	uint32 GameInstanceID;
	FGuid GameInstanceGUID;

	bool bDedicatedInstance;

	FString HubKey;

	TArray<AVRReplicatedMapInfo*> AllowedMaps;

};
