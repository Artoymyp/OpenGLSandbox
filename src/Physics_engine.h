#pragma once
#include "PhysX/PxPhysicsAPI.h"
#include <Face.h>
#include <LineDrawer.h>

using namespace physx;


class Callback_owner : public PxUserControllerHitReport, public PxControllerBehaviorCallback, public PxQueryFilterCallback
{

};

static const float gScaleFactor = 1.5f;
static const float gStandingSize = 1.0f * gScaleFactor;
static const float gCrouchingSize = 0.25f * gScaleFactor;
static const float gControllerRadius = 0.3f * gScaleFactor;


struct ControlledActorDesc
{
	ControlledActorDesc();

	PxControllerShapeType::Enum		mType;
	PxExtendedVec3					mPosition;
	float							mSlopeLimit;
	float							mContactOffset;
	float							mStepOffset;
	float							mInvisibleWallHeight;
	float							mMaxJumpHeight;
	float							mRadius;
	float							mHeight;
	float							mCrouchHeight;
	float							mProxyDensity;
	float							mProxyScale;
	float							mVolumeGrowth;
	PxUserControllerHitReport* mReportCallback;
	PxControllerBehaviorCallback* mBehaviorCallback;
};


struct Physics_engine {
	~Physics_engine() {
		if (_physics) {
			_physics->release();
			_physics = nullptr;
		}
		if (_cooking) {
			_cooking->release();
			_cooking = nullptr;
		}
		if (_pvd) {
			_pvd->release();
			_pvd = nullptr;
		}
		if (_foundation) {
			_foundation->release();
			_foundation = nullptr;
		}
		//PxCloseExtensions();
	}

	void init() {
		static PxDefaultErrorCallback gDefaultErrorCallback;
		static PxDefaultAllocator gDefaultAllocatorCallback;

		_foundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback,
			gDefaultErrorCallback);
		if (!_foundation)
			fatalError("PxCreateFoundation failed!");

		bool recordMemoryAllocations = false;

		bool visual_debug = false;
		if (visual_debug) {
			//mPvd = PxCreatePvd(*mFoundation);
			//char* PVD_HOST{ "address of the pvd app" };
			//PxPvdTransport* transport = PxDefaultPvdSocketTransportCreate(PVD_HOST, 5425, 10);
			//mPvd->connect(*transport, PxPvdInstrumentationFlag::eALL);
		}

		_physics = PxCreatePhysics(PX_PHYSICS_VERSION, *_foundation, PxTolerancesScale(), recordMemoryAllocations, _pvd);
		if (!_physics)
			fatalError("PxCreatePhysics failed!");

		bool need_cooking = true;
		if (need_cooking) {
			PxTolerancesScale scale;
			PxCookingParams params(scale);
			// disable mesh cleaning - perform mesh validation on development configurations
			params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_CLEAN_MESH;
			// disable edge precompute, edges are set for each triangle, slows contact generation
			params.meshPreprocessParams |= PxMeshPreprocessingFlag::eDISABLE_ACTIVE_EDGES_PRECOMPUTE;
			// lower hierarchy for internal mesh
			//params.meshCookingHint = PxMeshCookingHint::eCOOKING_PERFORMANCE;


			_cooking = PxCreateCooking(PX_PHYSICS_VERSION, *_foundation, PxCookingParams(scale));
			if (!_cooking)
				fatalError("PxCreateCooking failed!");

			_cooking->setParams(params);
		}

		bool need_extensions = false;
		if (need_extensions) {
			//if (!PxInitExtensions(*mPhysics, mPvd))
			//	fatalError("PxInitExtensions failed!");
		}
	}

	void create_terrain(const std::vector<Face>& faces) {

		for (unsigned int i = 0; i < faces.size() * 3; i++)
		{
			terrain_indexes.push_back(i);
		}

		PxTriangleMeshDesc meshDesc;
		meshDesc.points.count = faces.size() * 3;
		meshDesc.points.stride = sizeof(Vertex);
		meshDesc.points.data = &faces[0];

		meshDesc.triangles.count = faces.size();
		meshDesc.triangles.stride = 3 * sizeof(PxU32);
		meshDesc.triangles.data = &terrain_indexes[0];

#ifdef _DEBUG
		// mesh should be validated before cooked without the mesh cleaning
		bool res = _cooking->validateTriangleMesh(meshDesc);
		PX_ASSERT(res);
#endif

		PxTriangleMesh* triangleMesh = _cooking->createTriangleMesh(meshDesc, _physics->getPhysicsInsertionCallback());
		PxTriangleMeshGeometry triGeom;
		triGeom.triangleMesh = triangleMesh;

		PxTransform t;
		t.p = PxVec3(0,0,0);
		t.q = PxQuat(0, PxVec3(1,0,0));
		PxRigidStatic* actor = _physics->createRigidStatic(t);
		_material = _physics->createMaterial(0.5f, 0.5f, 0.1f);
		PxShape* shape = PxRigidActorExt::createExclusiveShape(*actor, triGeom, *_material);

		_scene->addActor(*actor);
	}
	std::vector<PxU32> terrain_indexes;

	void fatalError(std::string message) {
		throw std::exception(message.c_str());
	}

	void enable_visual_debug(PxScene* scene) {
		_visual_debugging_enabled = true;
		scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
		scene->setVisualizationParameter(
			//PxVisualizationParameter::eWORLD_AXES
			//PxVisualizationParameter::eACTOR_AXES
			PxVisualizationParameter::eCOLLISION_SHAPES
			//PxVisualizationParameter::eCOLLISION_FNORMALS
			
			, 2.0f);
	}

	void render_visual_debug(PxScene* scene, const glm::mat4& projection, const glm::mat4& view) {
		if (!_visual_debugging_enabled)
		{
			return;
		}
		const PxRenderBuffer& rb = scene->getRenderBuffer();
		for (PxU32 i = 0; i < rb.getNbLines(); i++)
		{
			const PxDebugLine& line = rb.getLines()[i];
			// render the line

			Line l{
				glm::vec3(line.pos0.x, line.pos0.y, line.pos0.z),
				glm::vec3(line.pos1.x, line.pos1.y, line.pos1.z) 
			};
			if (line.color0 != line.color1) {
				throw std::exception("Variable line color encountered during PhysX debug visualisation.");
			}
			l.setColor(glm::unpackUnorm4x8(line.color0));
			l.setMVP(projection * view);
			l.draw();
		}
	}
	void create_CCT(
		PxScene& scene, 
		PxExtendedVec3 controller_initial_position
	) {
		mControllerManager = PxCreateControllerManager(scene);

		/*
		_callback_owner = std::make_unique<Callback_owner>();

		ControlledActorDesc desc;
		desc.mType = PxControllerShapeType::eCAPSULE;
		desc.mPosition = controller_initial_position;
		desc.mSlopeLimit = 0.0f;
		desc.mContactOffset = 0.01f;
		desc.mStepOffset = 0.05f;
		desc.mInvisibleWallHeight = 0.0f;//6.0f
		desc.mMaxJumpHeight = 0.0f;//4.0f
		desc.mRadius = gControllerRadius;
		desc.mHeight = gStandingSize;
		desc.mCrouchHeight = gCrouchingSize;
		desc.mReportCallback = _callback_owner.get();
		desc.mBehaviorCallback = _callback_owner.get();
		{
			mActor = SAMPLE_NEW(ControlledActor)(*this);
			mActor->init(desc, mControllerManager);

			RenderBaseActor* actor0 = mActor->getRenderActorStanding();
			RenderBaseActor* actor1 = mActor->getRenderActorCrouching();
			if (actor0)
				mRenderActors.push_back(actor0);
			if (actor1)
				mRenderActors.push_back(actor1);
		}

		mCCTCamera = SAMPLE_NEW(SampleCCTCameraController)(*this);
		mCCTCamera->setControlled(&mActor, 0, 1);
		//	mCCTCamera->setFilterData();
		mCCTCamera->setFilterCallback(this);
		mCCTCamera->setGravity(-20.0f);

		setCameraController(mCCTCamera);

		mCCTCamera->setView(0, 0);
		*/
	}

	PxScene* create_scene() {
		PxSceneDesc sceneDesc(_physics->getTolerancesScale());
		sceneDesc.gravity = PxVec3(0.0f, -9.81f, 0.0f);

		// create CPU dispatcher which mNbThreads worker threads
		_cpu_dispatcher = PxDefaultCpuDispatcherCreate(0/*mNbThreads*/);
		if (!_cpu_dispatcher) {
			fatalError("PxDefaultCpuDispatcherCreate failed!");
		}
		sceneDesc.cpuDispatcher = _cpu_dispatcher;
		sceneDesc.filterShader = PxDefaultSimulationFilterShader;

		_scene = _physics->createScene(sceneDesc);

		_scene->setGravity(PxVec3(0.0f, -9.81f, 0.0f));



		return _scene;
	}

	bool _visual_debugging_enabled{ false };
	PxMaterial* _material{ nullptr };
	PxFoundation* _foundation{ nullptr };
	PxPvd* _pvd{ nullptr };
	PxPhysics* _physics{ nullptr };
	PxCooking* _cooking{ nullptr };
	PxDefaultCpuDispatcher* _cpu_dispatcher{ nullptr };
	PxScene* _scene{ nullptr };
	PxControllerManager* mControllerManager;

	std::unique_ptr<Callback_owner> _callback_owner;
};
