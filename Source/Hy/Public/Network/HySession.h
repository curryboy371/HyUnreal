// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class HY_API HySession : public TSharedFromThis<HySession>
{
public:
	HySession(class FSocket* Socket);
	~HySession();

	void Run();

	void Disconnect();

public:
	class FSocket* Socket;

};
