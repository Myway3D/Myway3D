/*
 * EMotion FX 2 - Character Animation System
 * Copyright (c) 2001-2004 Mystic Game Development - http://www.mysticgd.com
 * All Rights Reserved.
 */

#ifndef __MOTIONSYSTEM_H
#define __MOTIONSYSTEM_H

// include the core system
#include "../Core/Source/MCore.h"
#include "MotionInstance.h"
#include "MotionQueue.h"
#include "MemoryCategories.h"


namespace EMotionFX
{

// forward declarations
class Actor;

/**
 * The motion system base class.
 * A motion system has to manage how motions are being mixed and blended together.
 * When we make a call to Actor::PlayMotion(...) this system will have to handle the things which need to happen
 * in order to play this motion. Also when motions are stopped it has to handle this. Smooth transitions between
 * motions also have to be handled by this class, as well as the mixing of motions, where specific parts of the body
 * are overwritten by a given motion.
 * The motion system also contains a motion queue, which is responsible for some very basic scheduling of motions.
 */
class MotionSystem
{
	DECLARE_CLASS(MotionSystem);
	MEMORYOBJECTCATEGORY(MotionSystem, EMFX_DEFAULT_ALIGNMENT, MEMCATEGORY_MOTIONS_MOTIONSYSTEMS);
	friend class MotionQueue;

	public:
		/**
		 * Constructor.
 		 * @param actor The actor to which this layer belongs to.
		 */
		MotionSystem(Actor* actor);

		/**
		 * Destructor.
		 */
		virtual ~MotionSystem();

		/**
		 * Start playing the specified motion on this actor.
		 * @param motion The motion to play.
		 * @param info A pointer to an object containing playback information. This pointer is NOT allowed to be NULL here.
		 * @result A pointer to a created motion instance object. You can use this motion instance object to adjust and retrieve playback information at any time.
		 * @see PlayBackInfo
		 */
		virtual MotionInstance* PlayMotion(Motion* motion, class PlayBackInfo* info=NULL);

		/**
		 * Stop playing the motion in <blendTime> seconds.
		 * When <blendTime> is set to 0, it will be immediately stopped, which can cause a not so nice popping effects.
		 * When set to 1.0f, it would smoothly fade out the motion in exactly one second.
		 * @param motion The motion to play.
		 * @param blendTime The time in seconds until the motion has no influence anymore.
		 */
		virtual void StopMotion(MotionInstance* motion, const float blendTime) = 0;

		/**
		 * Test if there is currently a motion playing or active.
		 * Motions which are in pause mode, will also count. So in case of motions being paused, TRUE will be returned as well.
		 * @result True if there is a motion playing, false if not.
		 */
		virtual bool IsPlaying() const = 0;

		/**
		 * Get the unique motion system type ID.
		 * @result The motion system type identification number.
		 */
		virtual int GetType() const = 0;

		/**
		 * Get the type identification string.
		 * This can be a description or the class name of the motion system.
		 * @result A pointer to the string containing the name.
		 */
		virtual const char* GetTypeString() const = 0;

		/**
		 * Update this character motions, if <updateNodes> is false only time values are updated.
		 * If it's true, the heavy calcs (forward kinematics and other transformations) are done.
		 * NOTE: This method is automatically called by the Update method.
		 * @param timePassed The time passed since the last call-
		 * @param updateNodes If true the nodes will be updated.
		 */
		virtual void Update(const double timePassed, const bool updateNodes);

		/**
		 * Remove a given motion.
		 * @param nr The motion to remove.
		 * @param delMem If true the allocated memory of the motion will be deleted.
		 */
		inline void RemoveMotion(const int nr, const bool deleteMem=true);

		/**
		 * Remove a given motion.
		 * @param motion The motion to remove.
		 * @param delMem If true the allocated memory of the motion will be deleted.
		 */
		inline void RemoveMotion(MotionInstance* motion, const bool delMem=true);

		/**
		 * Removes a given motion instance from the actor, including all motion links in the nodes inside this Actor.
		 * @param instance The motion instance to remove.
		 * @result Returns true when everything went fine and will return false when the instance could not be removed
		 *         from any of these nodes or from this actor itself.
		 */
		bool RemoveMotionInstance(MotionInstance* instance);

		/**
		 * Get a given motion instance.
		 * Every motion instance inside an actor represents a motion which is currently playing or active inside
		 * the actor. Motion instances are automatically removed from the actor once they are not used anymore.
		 * This for example happens when a motion instance has finished playing.
		 * Before you do any calls to methods of a given motion instance, always first use the IsValidMotionInstance() method
		 * to check if the motion instance has not yet been removed from the actor (and from memory).
		 * @param nr The motion instance number to get.
		 * @result A pointer to the motion instance.
		 * @see IsValidMotionInstance
		 */
		inline MotionInstance* GetMotionInstance(const int nr) const;

		/**
		 * Recursively search for the first non mixing motion and return the motion instance.
		 * @result A pointer to the motion instance.
		 */
		virtual MotionInstance* FindFirstNonMixingMotionInst() = 0;

		/**
		 * Get the number of active motion instances inside this actor.
		 * Every motion instance inside an actor represents a motion which is currently playing or active inside
		 * the actor. Motion instances are automatically removed from the actor once they are not used anymore.
		 * This for example happens when a motion instance has finished playing.
		 * Before you do any calls to methods of a given motion instance, always first use the IsValidMotionInstance() method
		 * to check if the motion instance has not yet been removed from the actor (and from memory).
		 * @result The number of active motion instances inside this actor.
		 * @see IsValidMotionInstance
		 */
		inline int GetNumMotionInstances() const;

		/**
		 * Checks if a given motion instance is still valid.
		 * With valid we mean if it has not been deleted from memory yet. Because when a motion is stopped the motion instance
		 * will automatically be deleted from the Actor as well as from memory.
		 * You can validate if a given motion instance is still valid by passing it to this method.
		 * NOTE: Be sure to pass only motion instances which are returned by the PlayMotion method of this actor!
		 * Here follows some example code:
		 * <pre>
		 * Actor  *human = .....;     // assuming that human now contains a valid Actor.
		 * Actor  *orc = ....;        // assuming that orc now contains a valid Actor.
		 * Motion *walkMotion = ....; // assuming that walkMotion now contains a valid Motion.
		 * 
		 * // start playing the walk motion on the human
		 * MotionInstance *humanWalk = human->PlayMotion( walkMotion );
		 *
		 * // this is valid to execute, so no problems with this
		 * // isValid will be 'true' at this moment
		 * bool isValid  = human->IsValidMotionInfo( humanWalk );
		 * 
		 * // this is VERY WRONG! :)
		 * // you cannot validate a motion instance returned by the human on the orc
		 * // isValid2 will now contain 'false', while the motion is really still valid!
		 * // but it's simply not valid inside the orc...
		 * bool isValid2 = orc->IsValidMotionInfo( humanWalk );
		 * </pre>
		 */
		inline bool IsValidMotionInstance(MotionInstance* instance) const;

		/**
		 * Check if there is a motion instance playing which is an instance of a specified motion.
		 * This can be used to check if for example there currently is playing a 'walk' motion on a given actor.
		 * @param motion A pointer to the motion we want to check. So this method will answer the question
		 *               "Is there still an Actor::PlayMotion( motion ) active?"
		 * @result Returns true when there still is a motion instance active, which uses the specified motion, otherwise false is returned.
		 */
		inline bool IsPlayingMotion(Motion* motion) const;

		/**
		 * Set a new motion queue. Old one will be deleted.
		 * @param motionQueue The motion queue to set.
		 */
		inline void SetMotionQueue(MotionQueue* motionQueue);

		/**
		 * Add a motion queue to the motion system. All motions in the given
		 * motion queue will be put after the existing ones.
		 * @param motionQueue The motion queue to add.
		 */
		inline void AddMotionQueue(MotionQueue* motionQueue);

		/**
		 * Return motion queue pointer.
		 * @return A pointer to the motion queue.
		 */
		inline MotionQueue* GetMotionQueue() const;

		/**
		 * Return the actor to which this motion system belongs to.
		 * @return The actor to which this motion system belongs to.
		 */
		inline Actor* GetActor() const;

		/**
		 * Apply the motion mask of a given motion instance on a given transformation that will be applied on a given node.
		 * What this method does is overwrite the position, rotation and scale if the mask doesn't allow modifications of these.
		 * It will reset the transformation components back to the local values of the given node (Node::GetLocalPos(), Node::GetLocalRot() and Node::GetLocalScale()).
		 * @param nodeTransform The node transformation to apply modifications to (input and output).
		 * @param instance The motion instance to use the motion mask from.
		 * @param node The node to apply the transformation at.
		 */
		void ApplyMotionMask(NodeTransform* nodeTransform, MotionInstance* instance, Node* node);

	protected:
		Actor*							mActor;					/**< The parent actor (where this motion system belongs to). */
		MotionQueue*					mMotionQueue;			/**< The motion queue. */
		MCore::Array<MotionInstance*>	mMotionInstances;		/**< The collection of motion instances. */

		/**
		 * Start playing the specified motion on this actor.
		 * The difference with PlayMotion is that PlayMotion takes care of the calls to CreateMotionInstance, and handles the insertion into the motion queue, etc.
		 * This method should purely start the motion.
		 * @param motion The motion to play.
		 * @param info A pointer to an object containing playback information. This pointer is NOT allowed to be NULL here.
		 * @result A pointer to a created motion instance object. You can use this motion instance object to adjust and retrieve playback information at any time.
		 * @see PlayBackInfo
		 */
		virtual void StartMotion(MotionInstance* motion, class PlayBackInfo* info) = 0;

		/**
		 * Update the motion instances.
		 * @param timePassed The time passed since the last call.
		 */
		inline void UpdateMotionInstances(const double timePassed);

		/**
		 * Create the motion instance and add the motion info the parent actor.
		 * It also creates the motion links.
		 * @param motion The motion from which the system creates the instance from.
		 * @param info A pointer to the playback information.
		 * @return A pointer to the created motion instance.
		 */
		MotionInstance* CreateMotionInstance(Motion* motion, class PlayBackInfo* info);
};

// include inline code
#include "MotionSystem.inl"

} // namespace EMotionFX


#endif