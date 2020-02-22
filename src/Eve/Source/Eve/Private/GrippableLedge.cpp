// Fill out your copyright notice in the Description page of Project Settings.


#include "GrippableLedge.h"
#include "Eve/Eve.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGrippableLedge::AGrippableLedge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

    LedgeCollider = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LedgeCollider"));
    SetRootComponent(LedgeCollider);
    LedgeCollider->SetGenerateOverlapEvents(true);
    LedgeCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    LedgeCollider->SetCollisionObjectType(OBJECT_TYPE_TRAVERSAL);
    LedgeCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
    LedgeCollider->SetCollisionResponseToChannel(OBJECT_TYPE_CHARACTER_TRAVERSAL, ECR_Overlap);
    LedgeCollider->SetHiddenInGame(true);
    LedgeCollider->bVisible = true;

    DirectionalArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
    DirectionalArrow->AttachTo(LedgeCollider);
    DirectionalArrow->ArrowSize = 2.0f;
    DirectionalArrow->ArrowColor = FColor::Yellow;

}

// Called when the game starts or when spawned
void AGrippableLedge::BeginPlay()
{
	Super::BeginPlay();

}

FVector AGrippableLedge::GetUnitDirectionVectorToPosition_Implementation(FVector position)
{
    FVector direction = position - GetActorLocation();
    FVector2D dir2D = FVector2D(direction.X, direction.Y);

    FVector facingDirection = UKismetMathLibrary::GetForwardVector(GetActorRotation());
    FVector2D facingDirection2D = FVector2D(facingDirection.X, facingDirection.Y);

    facingDirection.Normalize();

    float dot = FVector2D::DotProduct(facingDirection2D, dir2D);
    if (dot >= 0) {
        return -facingDirection;
    }
    else {
        return facingDirection;
    }
}

// Called every frame
void AGrippableLedge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

