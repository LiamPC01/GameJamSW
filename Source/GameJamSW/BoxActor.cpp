// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxActor.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
ABoxActor::ABoxActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PitchValue = 0.f;
	YawValue = 0.f;
	RollValue = 0.f;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	CollisionBox->SetBoxExtent(FVector(32.f, 32.f, 32.f));
	CollisionBox->SetCollisionProfileName("Trigger");
	RootComponent = CollisionBox;

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABoxActor::OnOverlapBegin);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ABoxActor::OnOverlapEnd);
}

// Called when the game starts or when spawned
void ABoxActor::BeginPlay()
{
	Super::BeginPlay();

	GameJamSWCharacter = Cast<AGameJamSWCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ABoxActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FQuat QuatRotation = FQuat(FRotator(PitchValue, YawValue, RollValue));

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);

}

void ABoxActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GameJamSWCharacter && GameJamSWCharacter == OtherActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, "LEVEL COMPLETE");

	}
}

void ABoxActor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, "Overlap End Function Called");
}

